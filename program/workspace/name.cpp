
#include <iostream>

#include <ppl_c.h>
#include <ppl_test.hh>
#include <maplec.h>
#include <TangtongFunctions.cpp>
#include <TangtongPPL_header_c.cpp>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
string mapleresult;
const char *ch;
static void M_DECL textCallBack(void *data,int tag,const char *output){
    // std::cout<<output<<endl;
	mapleresult = output;
    ch = output;
}
bool processMapleStatement(MKernelVector &kv,char *maplestatement,string MapleOrder){
    TangtongMaple::ConstructMapleStatement(maplestatement,MapleOrder);
    EvalMapleStatement(kv,maplestatement);
    return true;
}

string ALG(MKernelVector kv, char *maplestatement, vector<string> LoopCons,vector<string> Cons, vector<string> variables){
    processMapleStatement(kv,maplestatement,"libname:=\"/home/tangtong/lib\",libname;");
    processMapleStatement(kv,maplestatement,"with(RegularChains): \
                                            with(SemiAlgebraicSetTools): \
                                            with(ArrayTools): \
                                            with(simplex): \
                                            with(LinearAlgebra): \
                                            with(linalg): \
                                            ");
	TangtongMaple::processFirstFarkasStatement(kv,maplestatement);
    processMapleStatement(kv, maplestatement, TangtongPPL::ConstructDeltaFromCons(LoopCons, Cons, variables));
    processMapleStatement(kv, maplestatement, TangtongPPL::ConstructOmega(LoopCons, Cons, variables));
    // processMapleStatement(kv,maplestatement,"Delta:={x1 - x = dx , \
    //                                             y1 - y = dy, \
    //                                             dx >= 0 , \
    //                                             dy1 <= dy , \
    //                                             dx1 <= dx + dy , \
    //                                             x >= 0 , \
    //                                             y1 <= y - 1 , \
    //                                             x1 <= x + y };");

	// processMapleStatement(kv,maplestatement,"Omega:={x >= 0 , y1 <= y - 1 , x1 <= x + y };");std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,Omega);");    std::cout<<mapleresult<<std::endl;
    //processMapleStatement(kv,maplestatement,"b:=1;k1:=1;k2:=1;k3:=1;");

    string generators,f,random_ei;
    int times = 1;
    const int ENDTIMES = 3;
    while(times <= ENDTIMES){
        std::cout<<"------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"The "<<times<<"th Iteration..."<<std::endl;
        processMapleStatement(kv,maplestatement,"solve(Delta,[" + TangtongPPL::ConstructAllVariablesFromVariables(variables,1) + "]);");//x,y,x1,y1,d_x,d_y,d_x1,d_y1]);");
        if(mapleresult == "[]"){
            std::cout<<"Delta has no solution. And there exists an LRF over Omega."<<std::endl;
            return "Delta has no solution. And there exists an LRF over Omega.";//break;
        }else{
            std::cout<<"Delta has solution . Use Farkas and ppl to calculate generators and construct an increasing function f(x)."<<std::endl;
            std::cout<<"Calculating...."<<std::endl;
            processMapleStatement(kv,maplestatement,"ret:=Farkas(Omega,[" + TangtongPPL::ConstructAllVariablesFromVariables(variables,0) + "]);");//x,y,x1,y1]);");
            std::cout<<"The result of calculating Omega using Farkas'Lemma are : "<<mapleresult<<endl;
            generators = TangtongPPL::InsertConstraints(TangtongPPL::AnalyzeFarkasRet(ch));
            f = TangtongPPL::ConstructOmega(generators,"x,y");
            random_ei = TangtongPPL::ConstructRandomEi();
            processMapleStatement(kv,maplestatement,random_ei);
            processMapleStatement(kv,maplestatement,f);std::cout<<mapleresult<<std::endl;
            processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,f);");std::cout<<mapleresult<<std::endl;
            processMapleStatement(kv,maplestatement,"Omega:=`union`(Omega,f);");std::cout<<mapleresult<<std::endl;
        }
        times++;
    }
    return "Delta has a solution. And there not exists an LRF over Omega.";
}

int main(int argc,char *argv[]){
	char err[2048];
	char *maplestatement = new char[4096];
    MKernelVector kv;
    ALGEB r,l;
    MCallBackVectorDesc cb = {textCallBack,0,0,0,
                            0,0,0,0};
    kv = StartMaple(argc,argv,&cb,NULL,NULL,err);


    vector<string> LoopCons,Cons,variables;
    LoopCons.push_back("0 <= x");
    // LoopCons.push_back("y <= -1");

    Cons.push_back("x <= x + y ");
    Cons.push_back("y <= y - 1 ");

    variables.push_back("x");
    variables.push_back("y");

    // TangtongPPL::ConstructDeltaFromCons(LoopCons, Cons, variables);
	std::cout<<ALG(kv, maplestatement, LoopCons, Cons, variables)<<std::endl;
	StopMaple(kv);
	return 0;
}
