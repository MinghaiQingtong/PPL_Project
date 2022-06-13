
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
double time_sum = 0;
double single_time = 0, Farkas_time = 0, PPL_time = 0;
int N = 5;
double tmp_time[5];
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

void MapleInit(MKernelVector kv, char *maplestatement) {
    processMapleStatement(kv,maplestatement,"restart;");
    processMapleStatement(kv,maplestatement,"libname:=\"/home/tangtong/lib\",libname;");
    processMapleStatement(kv,maplestatement,"with(RegularChains): \
                                            with(SemiAlgebraicSetTools): \
                                            with(ArrayTools): \
                                            with(simplex): \
                                            with(LinearAlgebra): \
                                            with(linalg): \
                                            ");
	TangtongMaple::processFirstFarkasStatement(kv, maplestatement);
    TangtongMaple::processStdFormat(kv, maplestatement);

}

string ALG(MKernelVector kv, char *maplestatement, vector<string> LoopCons,vector<string> Cons, vector<string> variables,int &counter){
    clock_t start,end;
    Farkas_time = 0;
    PPL_time = 0;

    processMapleStatement(kv, maplestatement, TangtongPPL::ConstructDeltaFromCons(LoopCons, Cons, variables));//cout<<mapleresult<<endl;
    processMapleStatement(kv, maplestatement, TangtongPPL::ConstructOmega(LoopCons, Cons, variables));//std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv, maplestatement,"Delta:=`union`(Delta,Omega);");    //std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv, maplestatement, "Omega:=StdFormat(Omega);");//cout<<mapleresult<<endl;
    
    string generators,GS,random_ei,LSVariable;
    LSVariable = TangtongPPL::ConstructAllVariablesFromVariables(variables,1);
    processMapleStatement(kv, maplestatement, "LSVariable:=["+ TangtongPPL::ConstructAllVariablesFromVariables(variables,1) +"];");//std::cout<<mapleresult<<std::endl;
    // end = clock();
    // tmp_time[1] += (double)(end-start)/CLOCKS_PER_SEC;
/////////////////
    
    const char *FarkasRetIsFalse = "{}";
    int cur_times = 1;
    const int ENDTIMES = 2;
    string k = "10";
    
//////////////////
    // start = clock();
    processMapleStatement(kv, maplestatement, "FixPCons:={"+ TangtongPPL::ConstructFixPCons(variables) +"};");//std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv, maplestatement, "FixPCons:=`union`(FixPCons,Omega);");//std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv, maplestatement, "simplex:-feasible(FixPCons);");
    // std::cout<<mapleresult<<std::endl;
    if(mapleresult != "false"){
        counter = 0;
        return "False";
    }
    // processMapleStatement(kv, maplestatement, "RegularChains:-SemiAlgebraicSetTools:-LinearSolve(convert(Delta,'list'),\
    //                                             PolynomialRing(LSVariable),\
    //                                             'projection' = nops(LSVariable));");std::cout<<mapleresult<<std::endl;
    processMapleStatement(kv, maplestatement, "simplex:-feasible(Delta);");
    // std::cout<<mapleresult<<std::endl;
    if(mapleresult == "false"){
            counter = 0;    
            return "True";//"Delta has a solution. And there exists an LRF over Omega.";
    }
    // end = clock();
    // tmp_time[2] += (double)(end-start)/CLOCKS_PER_SEC;
///////////////////
    while(cur_times <= ENDTIMES){
        //  std::cout<<"------------------------------------------------------------------------------"<<std::endl;
        //  std::cout<<"The "<<cur_times<<"th Iteration..."<<std::endl;
//////////////
        start = clock();
        // processMapleStatement(kv, maplestatement, "Omega;");cout<<"Omega := "<<mapleresult<<endl;
        processMapleStatement(kv, maplestatement, "nops(Omega);");//cout<<"l : "<<mapleresult<<endl;
        int l_count = atoi(mapleresult.c_str());
        processMapleStatement(kv,maplestatement,"Farkas(Omega,[" + TangtongPPL::ConstructAllVariablesFromVariables(variables,0) + "]);");//x,y,x1,y1]);");
        // std::cout<<"Farkas ret:"<<mapleresult<<std::endl;

        generators = TangtongPPL::InsertPPLConsByEMatrix(TangtongPPL::ConstructConsEMatrix(mapleresult, TangtongPPL::ConstructAllVariablesFromVariables(variables,-1), l_count));
        end = clock();
        Farkas_time += (double)(end-start)/CLOCKS_PER_SEC;

        //  std::cout<<"Generators:"<<generators<<std::endl;

        // return "STOP.";
//////////////
        // if(mapleresult == FarkasRetIsFalse){
        //     return "False2";//"Delta has no solution. And there not exists an LRF over Omega.";
        // }
/////////////
        // start = clock();
        // string temp_str = TangtongPPL::AnalyzeFarkasRet(mapleresult);
        // std::cout<<"temp_str:"<<temp_str<<endl;
        // end = clock();
        // tmp_time[3] += (double)(end-start)/CLOCKS_PER_SEC;
///////////
///////////////
        // start = clock();
        // generators = TangtongPPL::InsertConstraints(temp_str, TangtongPPL::ConstructAllVariablesFromVariables(variables,-1)); // Farkas -> ci -> ppl -> generators
        // std::cout<<"generators:"<<generators<<std::endl;
        // end = clock();
        // PPL_time += (double)(end-start)/CLOCKS_PER_SEC;
        // return "STOP.";
//////////////    
        if(generators.empty()){
            return "PPL Calculate Overflow...";
        }
//////////////
        start = clock();
        vector<string> GS = TangtongPPL::ConstructGeneratorsConstraints(generators,TangtongPPL::ConstructAllVariablesFromVariables(variables,-1),k);
        
        // std::cout<<"GS:"<<GS<<std::endl;
        if(GS.size() <= 0) {
            return "CACULATE OVERFLOW!";
        }
        
        processMapleStatement(kv,maplestatement,GS[0]);//std::cout<<mapleresult<<std::endl;

        processMapleStatement(kv, maplestatement, "nops(GS1);");//cout<<"nops(GS1):"<<mapleresult<<endl;
        int GS1Size = stoi(mapleresult);
        if(GS1Size > 100) {
            return "CACULATE OVERFLOW!";
        }
        processMapleStatement(kv, maplestatement, GS[1]);//cout<<mapleresult<<endl;
        processMapleStatement(kv, maplestatement, "nops(GS2);");
        int GS2Size = stoi(mapleresult);
        if(GS2Size > 100) {
            return "CACULATE OVERFLOW!";
        }

        
        processMapleStatement(kv,maplestatement,"Omega:=`union`(Omega,GS1);");//std::cout<<mapleresult<<std::endl;
        
        processMapleStatement(kv,maplestatement,"Delta:=`union`(Delta,GS1,GS2);");//std::cout<<mapleresult<<std::endl;
        end = clock();
        // PPL_time += (double)(end-start)/CLOCKS_PER_SEC;
/////////////////
        // processMapleStatement(kv,maplestatement,"f := `&E`([" + TangtongPPL::ConstructAllVariablesFromVariables(variables,1) + "]), `&and`(seq(Delta[i], i = 1 .. nops(Delta)));");
        // std::cout<<mapleresult<<std::endl;
        //processMapleStatement(kv, maplestatement, "LSVariable:=[op(LSVariable),k"+ to_string(cur_times) +"];");
        //std::cout<<mapleresult<<std::endl;
        // processMapleStatement(kv,maplestatement,"RegularChains:-SemiAlgebraicSetTools:-QuantifierElimination(f, output = rootof, optimization = false);");
        // processMapleStatementkv, maplestatement, 
        // processMapleStatement(kv, maplestatement, "RegularChains:-SemiAlgebraicSetTools:-LinearSolve(convert(Delta,'list'),\
        //                                             PolynomialRing(LSVariable),\
        //                                             'projection' = nops(LSVariable));");
        // cout<<111<<endl;
        // processMapleStatement(kv,maplestatement, "Delta;");cout<<mapleresult<<endl;
        processMapleStatement(kv,maplestatement,"nops(Delta);");//cout<<mapleresult<<endl;
        int DeltaSize = stoi(mapleresult);
        if(DeltaSize > 100){
            return "CACULATE OVERFLOW!";
        } 
        processMapleStatement(kv,maplestatement, "simplex:-feasible(Delta);");//cout<<mapleresult<<endl;


        // processMapleStatement(kv, maplestatement, "minimize(1, Delta);");
                                                    
                                                    //'projection'="+ to_string(cur_times) +");");
        // std::cout<<mapleresult<<std::endl;
        
        if(mapleresult == "false"){
            counter = cur_times;    
            return "True";//"Delta has a solution. And there exists an LRF over Omega.";
        }
        //processMapleStatement(kv, maplestatement, "k:=[op(k), k"+ to_string(cur_times) +"];");
        //std::cout<<mapleresult<<std::endl;
        cur_times++;
    }
    counter = cur_times;
    return "Unknown";//"Delta has no solution. And there not exists an LRF over Omega.";
}

void test(MKernelVector kv, char *maplestatement){
    fstream fs;
    // fs.open("data",ios::in);
    fs.open("svcomp",ios::in);
    ofstream ofs;
    ofs.open("output",ios::out);
    int cases_num = 0;
    int num;
    string str;
    fs>>cases_num;
    vector<string> LoopCons,Cons,Variables;

    MapleInit(kv, maplestatement);

    for(int i = 0; i < cases_num; i++){
        fs>>num;
        // cout<<"The "<<num<<"th cases:----------------------------------"<<endl;
        // ofs<<"The "<<num<<"th cases : ";
        ofs<<num<<" ";

        LoopCons.clear();
        Cons.clear();
        Variables.clear();
        
        fs>>num;
        for(int j = 0; j < num; j++){
            fs>>str;
            //ofs<<str<<" ";
            LoopCons.push_back(str);
        }
        fs>>num;
        for(int j = 0; j < num; j++){
            fs>>str;
            //ofs<<str<<" ";
            if(str.find("=") == string::npos){
                // cout<<"Input ERROR!"<<endl;
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
        clock_t start,end;

        start = clock();
        str = ALG(kv, maplestatement, LoopCons, Cons, Variables, counter);
        
        end = clock();
        
        single_time = (double)(end-start)/CLOCKS_PER_SEC;
        // std::cout<<"Runtime:"<<(double)(end-start)/CLOCKS_PER_SEC<<"s."<<endl;
        // if(str == "True")
            time_sum += single_time;
        // cout<<str<<endl;
        // cout<<endl;
        // ofs<<" counter = "<<counter;
        ofs<<counter<<" "<<str<<" "<<single_time<<"s.";
        // ofs<<"  termination = "<<str;
        // ofs<<" Runtime:"<<single_time<<"s."<<Farkas_time<<"s.";
        // for(int i = 1; i < N; i++){
        //     ofs<<" "<<tmp_time[i];
        // }
        ofs<<std::endl;
        // if(str == "Delta has a solution. And there exists an LRF over Omega."){
        //     ofs<<" Exist LRF."<<endl;
        // }else{//"Delta has no solution. And there not exists an LRF over Omega."
        //     ofs<<" Not Exit."<<endl;
        // }
        
    }
    ofs<<"SUM Runtime:"<<time_sum<<"s."<<endl;
    fs.close();
    ofs.close();

}
int main(int argc,char *argv[]){
    clock_t start,end;
    

	char err[2048];
	char *maplestatement = new char[4096];
    MKernelVector kv;
    ALGEB r,l;
    MCallBackVectorDesc cb = {textCallBack,0,0,0,
                            0,0,0,0};
    kv = StartMaple(argc,argv,&cb,NULL,NULL,err);
    // start = clock();
    std::cout<<"Start:"<<std::endl;
    test(kv,maplestatement);
    std::cout<<"End...."<<std::endl;
    // end = clock();
    // StopMaple(kv);
    // cout<<"end maple"<<endl;
	// std::cout<<ALG(kv, maplestatement, LoopCons, Cons, variables)<<std::endl;
	
    std::cout<<"SUM Runtime:"<<time_sum<<"s."<<endl;
    // std::cout<<(double)(end-start)/CLOCKS_PER_SEC<<" s."<<std::endl;
	return 0;
}
