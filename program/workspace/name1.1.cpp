
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
    processMapleStatement(kv, maplestatement, TangtongPPL::ConstructOmega(LoopCons, Cons, variables));std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,Omega);");    std::cout<<mapleresult<<std::endl;

    string generators,GS,random_ei;
    int cur_times = 1;
    const int ENDTIMES = 3;
    while(cur_times <= ENDTIMES){
        std::cout<<"------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"The "<<cur_times<<"th Iteration..."<<std::endl;
        processMapleStatement(kv,maplestatement,"ret:=Farkas(Omega,[" + TangtongPPL::ConstructAllVariablesFromVariables(variables,0) + "]);");//x,y,x1,y1]);");
        std::cout<<mapleresult<<std::endl;
        generators = TangtongPPL::InsertConstraints(TangtongPPL::AnalyzeFarkasRet(mapleresult));
        GS = TangtongPPL::ConstructGeneratorsConstraints(generators,TangtongPPL::ConstructAllVariablesFromVariables(variables,-1),cur_times);std::cout<<GS<<std::endl;
        processMapleStatement(kv,maplestatement,GS);std::cout<<mapleresult<<std::endl;
        processMapleStatement(kv,maplestatement,"Omega:=`union`(Omega,GS1);");std::cout<<mapleresult<<std::endl;
        processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,GS1,GS2);");std::cout<<mapleresult<<std::endl;
        processMapleStatement(kv,maplestatement,"f := `&E`([" + TangtongPPL::ConstructAllVariablesFromVariables(variables,1) + "]), `&and`(seq(Delta[i], i = 1 .. nops(Delta)));");
        std::cout<<mapleresult<<std::endl;
        processMapleStatement(kv,maplestatement,"RegularChains:-SemiAlgebraicSetTools:-QuantifierElimination(f, output = rootof, optimization = false);");
        if(mapleresult != "true"){
            return "Delta has no solution. And there exists an LRF over Omega.";
        }
        cur_times++;
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
    LoopCons.push_back("y <= -1");

    Cons.push_back("x <= x + y ");
    Cons.push_back("y <= y - 1 ");

    variables.push_back("x");
    variables.push_back("y");

	std::cout<<ALG(kv, maplestatement, LoopCons, Cons, variables)<<std::endl;
	StopMaple(kv);
	return 0;
}
