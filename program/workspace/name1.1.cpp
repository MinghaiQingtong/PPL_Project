
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
#include <fstream>
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

string ALG(MKernelVector kv, char *maplestatement, vector<string> LoopCons,vector<string> Cons, vector<string> variables,int &counter){
    processMapleStatement(kv,maplestatement,"restart;");
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
    //processMapleStatement(kv, maplestatement, "k:=[];");
    string generators,GS,random_ei,LSVariable;
    LSVariable = TangtongPPL::ConstructAllVariablesFromVariables(variables,1);
    processMapleStatement(kv, maplestatement, "LSVariable:=["+ TangtongPPL::ConstructAllVariablesFromVariables(variables,1) +"];");std::cout<<mapleresult<<std::endl;

    const char *FarkasRetIsFalse = "{}";
    int cur_times = 1;
    const int ENDTIMES = 3;
    string k = "-10";
    while(cur_times <= ENDTIMES){
        std::cout<<"------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"The "<<cur_times<<"th Iteration..."<<std::endl;

        processMapleStatement(kv,maplestatement,"Farkas(Omega,[" + TangtongPPL::ConstructAllVariablesFromVariables(variables,0) + "],k);");//x,y,x1,y1]);");
        std::cout<<mapleresult<<std::endl;
        
        if(mapleresult == FarkasRetIsFalse){
            return "Delta has no solution. And there not exists an LRF over Omega.";
        }
        
        string temp_str = TangtongPPL::AnalyzeFarkasRet(mapleresult);
         std::cout<<"temp_str:"<<temp_str<<endl;
        
        generators = TangtongPPL::InsertConstraints(temp_str, TangtongPPL::ConstructAllVariablesFromVariables(variables,-1));
        // std::cout<<"generators:"<<generators<<std::endl;
        if(generators.empty()){
            return "ERROR.";
        }
        GS = TangtongPPL::ConstructGeneratorsConstraints(generators,TangtongPPL::ConstructAllVariablesFromVariables(variables,-1),k);std::cout<<GS<<std::endl;
        
        processMapleStatement(kv,maplestatement,GS);std::cout<<mapleresult<<std::endl;
        
        processMapleStatement(kv,maplestatement,"Omega:=`union`(Omega,GS1);");std::cout<<mapleresult<<std::endl;
        
        processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,GS1,GS2);");std::cout<<mapleresult<<std::endl;
        
        // processMapleStatement(kv,maplestatement,"f := `&E`([" + TangtongPPL::ConstructAllVariablesFromVariables(variables,1) + "]), `&and`(seq(Delta[i], i = 1 .. nops(Delta)));");
        // std::cout<<mapleresult<<std::endl;
        //processMapleStatement(kv, maplestatement, "LSVariable:=[op(LSVariable),k"+ to_string(cur_times) +"];");
        std::cout<<mapleresult<<std::endl;
        // processMapleStatement(kv,maplestatement,"RegularChains:-SemiAlgebraicSetTools:-QuantifierElimination(f, output = rootof, optimization = false);");
        // processMapleStatementkv, maplestatement, 
        processMapleStatement(kv, maplestatement, "RegularChains:-SemiAlgebraicSetTools:-LinearSolve(convert(Delta,'list'),\
                                                    PolynomialRing(LSVariable),\
                                                    'projection' = nops(LSVariable));");
                                                    
                                                    //'projection'="+ to_string(cur_times) +");");
        std::cout<<mapleresult<<std::endl;
        
        if(mapleresult == "[]"){
            counter = cur_times;    
            return "Delta has a solution. And there exists an LRF over Omega.";
        }
        //processMapleStatement(kv, maplestatement, "k:=[op(k), k"+ to_string(cur_times) +"];");
        std::cout<<mapleresult<<std::endl;
        cur_times++;
    }
    counter = cur_times;
    return "Delta has no solution. And there not exists an LRF over Omega.";
}

void test(MKernelVector kv, char *maplestatement){
    fstream fs;
    fs.open("data",ios::in);
    ofstream ofs;
    ofs.open("output",ios::out);
    int cases_num = 0;
    int num;
    string str;
    fs>>cases_num;
    vector<string> LoopCons,Cons,Variables;

    for(int i = 0; i < cases_num; i++){
        fs>>num;
        cout<<"The "<<num<<"th cases:----------------------------------"<<endl;
        ofs<<"The "<<num<<"th cases : ";

        LoopCons.clear();
        Cons.clear();
        Variables.clear();
        
        fs>>num;
        for(int j = 0; j < num; j++){
            fs>>str;
            ofs<<str<<" ";
            LoopCons.push_back(str);
        }
        fs>>num;
        for(int j = 0; j < num; j++){
            fs>>str;
            ofs<<str<<" ";
            if(str.find("=") == string::npos){
                cout<<"Input ERROR!"<<endl;
            }
            else if(str.find(">") == string::npos && str.find("<") == string::npos){
                int e_pos = str.find("=");
                string temp_str = str;
                str.insert(e_pos,"<");
                Cons.push_back(str);
                temp_str.insert(e_pos,">");
                Cons.push_back(temp_str);
            }else{
                Cons.push_back(str);
            }
            //Cons.push_back(str);
        }
        fs>>num;
        for(int j = 0; j < num; j++){
            fs>>str;
            Variables.push_back(str);
        }
        int counter = 1;
        str = ALG(kv, maplestatement, LoopCons, Cons, Variables, counter);
        cout<<str<<endl;
        cout<<endl;
        ofs<<" counter="<<counter;
        if(str == "Delta has a solution. And there exists an LRF over Omega."){
            ofs<<" Exist LRF."<<endl;
        }else{//"Delta has no solution. And there not exists an LRF over Omega."
            ofs<<" Not Exit."<<endl;
        }
        
    }
    fs.close();
    ofs.close();

}
int main(int argc,char *argv[]){
	char err[2048];
	char *maplestatement = new char[4096];
    MKernelVector kv;
    ALGEB r,l;
    MCallBackVectorDesc cb = {textCallBack,0,0,0,
                            0,0,0,0};
    kv = StartMaple(argc,argv,&cb,NULL,NULL,err);

    test(kv,maplestatement);
    // vector<string> LoopCons,Cons,variables;
    // LoopCons.push_back("0 <= x");
    // LoopCons.push_back("x <= 100");

    // Cons.push_back("2*x <= x");
    // Cons.push_back("-2*x <= x ");

    // variables.push_back("x");
    // variables.push_back("y");

	// std::cout<<ALG(kv, maplestatement, LoopCons, Cons, variables)<<std::endl;
	StopMaple(kv);
	return 0;
}
