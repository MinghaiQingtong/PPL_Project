#ifndef _TangtongPPL_Header_C
#define _TangtongPPL_Header_C

#include <ppl_c.h>
#include <ppl_test.hh>
#include <cstring>
// #include <maplec.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
// using namespace std;


namespace TangtongPPL{

    bool PrintStringVector(vector<string> vs){
        std::cout<<"Print String Vector"<<std::endl;
        for(int i = 0 ; i < vs.size() ; i++){
            std::cout<<vs[i]<<std::endl;
        }
        std::cout<<"End Print."<<std::endl;
    }


    void DeleteBlanks(string &constraints){
        for(int i = 0 ; i < constraints.length() ; ){
            if(constraints[i] == ' ')
                constraints.erase(i,1);
            else
                i++;
        }
        if(constraints[0] == '{')
            constraints.erase(0,1);
        if(constraints[constraints.length() - 1] == '}')
            constraints.erase(constraints.length() - 1 , 1);
    }
    vector<string> DivideConstraints(string constraints,char split){
        // std::cout<<constraints<<"1111"<<split<<std::endl;
        vector<string> subs;
        int l = 0 , r = constraints.length() - 1 , len = 0;
        while(constraints[l] == split) l++;
        while(constraints[r] == split) r--;
        for(int i = l ; i <= r ; i++){
            if(constraints[i] == split){
                subs.push_back(constraints.substr(i - len,len));
                len = 0;
            }else{
                len++;
            }
        }
        subs.push_back(constraints.substr(r - len + 1 , len));
        for(int i = 0 ; i < subs.size() ; i++){
            // std::cout<<subs[i]<<"--";
        }
        return subs;
    }
    vector<string> DivideConstraints(string constraints,string split){
        vector<string> subs;
        int l = 0 , r = constraints.length() - 1 , len = 0 ;
        
        for(l = 0 ; l < constraints.length() - split.length() + 1; ){
            if(constraints.substr(l,split.length()) == split && len != 0){
                subs.push_back(constraints.substr(l - len , len));
                len = 0;
            }else if(constraints.substr(l,split.length()) == split && len == 0){
                l = l + split.length();
            }else{
                l++;len++;
            }
        }
        if(len != 0) subs.push_back(constraints.substr(constraints.length() - len + 1 , len));
        // for(int i = 0 ; i < subs.size() ; i++)
        //     std::cout<<subs[i]<<"---";
        // std::cout<<std::endl;
        return subs;
    }

    /*
        
     */
    vector<string> GetParas(string constraints){//Do not support c[10] or more
        vector<string> paras;
        int max = 0;
        for(int i = 1 ; i < constraints.length() - 1 ; i++ ){
            if(constraints[i-1] == '[' && constraints[i+1] == ']')
                max = max > (int)constraints[i]-48 ? max : (int)constraints[i]-48;
        }
        for(int i = 1 ; i <= max ; i++ ){
            string para = "c[x]";
            para[2] = (char)i+48;
            paras.push_back(para);
        }
        return paras;
    }

    string changeSymbol(string str, string sym1, string sym2){
        while(str.find(sym1) != str.npos){
            str.replace(str.find(sym1), sym1.size(), sym2);
            // cout<<str<<endl;
        }
        // cout<<"end"<<endl;
        return str;
    }


    /*
        Reverse constraints . Let 0 <= c[1] + c[2] + 3 become -c[1] - c[2] - 3 <= 0 standard format.
     */
    void AdjustCons(vector<string> &cons){
        // std::cout<<"Start AdjustCons():"<<cons.size()<<std::endl;
        // PrintStringVector(cons);
        for(int i = 0 ; i < cons.size() ; i++){
            // std::cout<<"111";
            // std::cout<<"AdjustCons:"<<cons[i]<<" ";
            //when c[1]=0 tranform it into c[1]<=0 and -c[1]<=-0
            string temp_str = cons[i];
            if(cons[i].find("<") == cons[i].npos){
                cons[i].insert(cons[i].find("="), "<");
                temp_str.insert(temp_str.find("="), "<");
                if(temp_str[0] != '-' && temp_str[0] != '0'){
                    temp_str.insert(0, "+");
                }
                if(temp_str[temp_str.find("=") + 1] != '-' && temp_str[temp_str.find("=") + 1] != '0'){
                    temp_str.insert(temp_str.find("=")+1, "+");
                }
                temp_str = changeSymbol(temp_str, "+", "$");
                temp_str = changeSymbol(temp_str, "-", "%");
                temp_str = changeSymbol(temp_str, "$", "-");
                temp_str = changeSymbol(temp_str, "%", "+");
              //  std::cout<<"temp_str:"<<temp_str<<std::endl;
                cons.push_back(temp_str);

            }
            int e_pos = 0;
            while(cons[i][e_pos] != '=')
                e_pos++;
            int r = e_pos + 1 , l = e_pos + 1;
            string c_con = cons[i].substr(e_pos+1,cons[i].length()-e_pos-1);
            for(int j = 0; j < c_con.length() ; j++){
                if(c_con[j] == '-'){
                    c_con.insert(j,"+");
                    j++;
                }
            }
            vector<string> coeff = DivideConstraints(c_con,'+');

            for(vector<string>::iterator it = coeff.begin() ; it != coeff.end() ; ){
                if((*it) == "0" )
                    coeff.erase(it);
                else
                    it++;	
            }
            cons[i].replace(e_pos + 1,cons[i].length() - e_pos - 1,"0");
            if(cons[i][0] == '0'){
                cons[i].erase(0,1);
            }else if(cons[i][0] != '-'){
                cons[i].insert(0,"+");
            }
            for(int j = 0 ; j < coeff.size() ; j++ ){
                if(coeff[j][0] == '-'){
                    string c_coeff = coeff[j].substr(1,coeff[j].length()-1);
                    cons[i].insert(0,c_coeff);
                    cons[i].insert(0,"+");
                }else{
                    string c_coeff = coeff[j].insert(0,"-");
                    cons[i].insert(0,c_coeff);
                }
            }
        }
        // std::cout<<"222"<<std::endl;
    }
    Variable A(0) , B(1) , C(2) , D(3) , E(4) , F(5) , G(6) , H(7) , I(8) , J(9);
    Constraint_System cs;
    void DoInsert(int c_e[],int c_divisor[],int para_size){
        // std::cout<<"DO INSERT : "<<para_size<<std::endl;
        int mul = 1;
        for(int i = 0 ; i <= para_size ; i++){
            mul*=c_divisor[i];
        }
        if(para_size == 1){
        
            cs.insert(mul/c_divisor[0]*c_e[0]*A + mul/c_divisor[1]*c_e[1] <= 0);
        
        }else if(para_size == 2){
            // std::cout<<mul<<" "<<c_e[0]<<" "<<c_divisor[0]<<" "<<c_e[1]<<" "<<c_divisor[1]<<" "<<c_e[2]<<" "<<c_divisor[2]<<" "<<std::endl;
            cs.insert(mul/c_divisor[0]*c_e[0]*A + mul/c_divisor[1]*c_e[1]*B + mul/c_divisor[2]*c_e[2] <= 0);
            // cs.insert(c_divisor[0]*c_divisor[1]*c_divisor[2]*c_e[0]/c_divisor[0]*A + c_divisor[0]*c_divisor[1]*c_divisor[2]*c_e[1]/c_divisor[1]*B + c_divisor[0]*c_divisor[1]*c_divisor[2]*c_e[2]/c_divisor[2] <= 0);
        
        }else if(para_size == 3){

            cs.insert(mul/c_divisor[0]*c_e[0]*A + mul/c_divisor[1]*c_e[1]*B + mul/c_divisor[2]*c_e[2]*C + mul/c_divisor[3]*c_e[3] <= 0);
        
        }else if(para_size == 4){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D 
            + mul*c_e[4]/c_divisor[4] <= 0);
        
        }else if(para_size == 5){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5] <= 0);

        }else if(para_size == 6){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5]*F + mul*c_e[6]/c_divisor[6] <= 0);

        }else if(para_size == 7){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5]*F + mul*c_e[6]/c_divisor[6]*G + mul*c_e[7]/c_divisor[7] <= 0);

        }else if(para_size == 8){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5]*F + mul*c_e[6]/c_divisor[6]*G + mul*c_e[7]/c_divisor[7]*H 
            + mul*c_e[8]/c_divisor[8] <= 0);

        }else if(para_size == 9){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5]*F + mul*c_e[6]/c_divisor[6]*G + mul*c_e[7]/c_divisor[7]*H 
            + mul*c_e[8]/c_divisor[8]*I + mul*c_e[9]/c_divisor[9] <= 0);

        }else if(para_size == 10){

            cs.insert(mul*c_e[0]/c_divisor[0]*A + mul*c_e[1]/c_divisor[1]*B + mul*c_e[2]/c_divisor[2]*C + mul*c_e[3]/c_divisor[3]*D
            + mul*c_e[4]/c_divisor[4]*E + mul*c_e[5]/c_divisor[5]*F + mul*c_e[6]/c_divisor[6]*G + mul*c_e[7]/c_divisor[7]*H 
            + mul*c_e[8]/c_divisor[8]*I + mul*c_e[9]/c_divisor[9]*J + mul*c_e[10]/c_divisor[10] <= 0);
            
        }

    }
    void iInsert(vector<string> cons, vector<string> paras, int var_size){
        //////////////////////
        // std::cout<<"iInsert():"<<std::endl;
        // for(int i = 0; i < cons.size(); i++){
        //     std::cout<<cons[i]<<" ";
        // }std::cout<<std::endl;
        ////////////////////////
        for(int i = 0 ; i < cons.size() ; i++){
            for(int j = 0 ; j < cons[i].length() ; j++){
                if(cons[i][j] == '-' || cons[i][j] == '<'){
                    cons[i].insert(j,"+");
                    j++;
                }
            }
            //std::cout<<cons[i]<<std::endl;;
            vector<string> coeff = DivideConstraints(cons[i],'+');
            // for(int j = 0 ; j < coeff.size()-1 ; j++)
            //     std::cout<<coeff[j]<<" ";
            // std::cout<<std::endl;
            int c_e[11] = {0},c_divisor[11] = {1,1,1,1,1,1, 1,1,1,1,1};

            for(int j = 0; j < coeff.size()-1 ; j++){
                int tag=0;
                for(int p = 0; p <  var_size; p++){//1
                    int idx = coeff[j].find(paras[p]);
                    if(idx > -1){
                        int div_pos = coeff[j].find("/");
                        int mul_pos = coeff[j].find("*");
                        if(div_pos > -1 && mul_pos > -1){
                            c_e[p] = atoi(coeff[j].substr(0,div_pos).c_str());
                            c_divisor[p] = atoi(coeff[j].substr(div_pos+1,mul_pos-div_pos-1).c_str());
                        }else if(div_pos == -1 && mul_pos > -1){
                            c_e[p] = atoi(coeff[j].substr(0,mul_pos).c_str());
                        }else{
                            if(coeff[j][0] == '-')
                                c_e[p] = -1;
                            else
                                c_e[p] = 1;
                        }
                        tag = 1;
                        break;
                    }
                }
                if(tag == 0){
                    int div_pos = coeff[j].find("/");
                    if(div_pos > -1){
                        c_e[var_size] = atoi(coeff[j].substr(0,div_pos).c_str());
                        c_divisor[var_size] = atoi(coeff[j].substr(div_pos+1,coeff[j].length()-div_pos-1).c_str());
                    }else{
                        c_e[var_size] = atoi(coeff[j].c_str());
                    }
                }
            }
            // std::cout<<"c_e c_divisor:"<<std::endl;
            // for(int j = 0 ; j < 10 ; j++){
            //     std::cout<<c_e[j]<<" "<<c_divisor[j]<<std::endl;
            // }
            DoInsert(c_e,c_divisor,var_size);
        }
    }


/*
 *      if cons have strict equalities like c[1]<1
 *      then add a "=" after "<"
 *      because ppl cannot handle strict equalities.
 */
    void AddEqu(vector<string> &cons){
        for(int i = 0; i < cons.size(); i++){
            int pos = 0;
            pos = cons[i].find(">");
            if(pos != string::npos && cons[i][pos+1] != '='){
                cons[i].insert(pos+1, "=");
            }
            pos = cons[i].find("<");
            if(pos != string::npos && cons[i][pos+1] != '='){
                cons[i].insert(pos+1, "=");
            }

        }
    }

    void InsertCons(vector<string> cons, vector<string> paras, int var_size){
        // PrintStringVector(cons);
        AddEqu(cons);
        // PrintStringVector(cons);
        AdjustCons(cons);
        // PrintStringVector(cons);
        iInsert(cons,paras,var_size);
        //std::cout<<"cons:"<<cons.size()<<std::endl;
    }

    string InsertConstraints(string ch, string variables){
        cs.initialize();
        cs.clear();
        vector<string> cons,paras;
        string constraints = ch;
        int var_size = DivideConstraints(variables,",").size();
        DeleteBlanks(constraints);
        std::cout<<"constraints:"<<constraints<<endl;
        paras = GetParas(constraints);
        cons = DivideConstraints(constraints,',');
        /////////////////////
        // for(int i = 0; i < paras.size(); i++){
        //     std::cout<<paras[i]<<" ";
        // }std::cout<<endl;
        // for(int i = 0; i < cons.size(); i++){
        //     std::cout<<cons[i]<<" ";
        // }std::cout<<endl;
        /////////////////////
        InsertCons(cons,paras,var_size);
        cs.print();std::cout<<std::endl;
        C_Polyhedron cp(cs);
        //cp.initialize();cp.finalize();
        std::cout<<"Constraints System : ";cp.print();std::cout<<std::endl;;
        Generator_System gs = cp.generators();gs.finalize();
        std::cout<<"Generators : ";gs.print();std::cout<<std::endl;
        cs.finalize();
        if(gs.print_tt() == ""){
            std::cout<<"Calculate Overflow."<<std::endl;
            return "";
        }
        return gs.print_tt();
    }

    /*
        f(x) = a^T*x + b
        a^T = Sigma(ri*Pi) + Sigma(ui*Ri) + Sigma(di*Li)
        Sigma ri = 1 , ri >= 0 , ui >= 0 , di belong to Real number.
        Pi represent Points.Ri represent Rays.Li represent Lines.
        
        The strategy to construct Omega simply is to let ri = 0 but r1 = 1, and ui = 0, di = 0.
        There are taking this strategy.
    
     */
    string ConstructGeneratorsConstraints(string gs_coeffs,string x){
        vector<string> v_gs_coeffs = DivideConstraints(gs_coeffs,"(C)");
        vector<string> v_x = DivideConstraints(x,',');
        int p_pos = 0;
        while(p_pos < v_gs_coeffs.size()){
            int len = v_gs_coeffs[p_pos].length();
            if(v_gs_coeffs[p_pos][len - 2] == 'P'){
                break;
            }
            p_pos++;
        }
        if(p_pos == v_gs_coeffs.size()){
            std::cout<<"DATA ERROR!"<<std::endl;
            return "FALSE";
        }
        vector<string> f_coeff = DivideConstraints(v_gs_coeffs[p_pos],' ');
        string f = "f:={";
        
        for(int i = 3 ; i < 3 + v_x.size() ; i++){
            if(f_coeff[i][0] != '-'){
                f.append("+");
            }
            f.append(f_coeff[i]+"/"+f_coeff[2]+"*"+v_x[i-3]);
        }
        f.append(" >= ei };");
        //std::cout<<f<<std::endl;
        return f;
    }

    string ConstructGeneratorsConstraints(string gs_coeffs, string variables, string k /* int cur_times */){
        // std::cout<<"Start GS:"<<std::endl;
        // std::cout<<"gs_coeffs:"<<gs_coeffs<<std::endl;
        // std::cout<<"variables:"<<variables<<std::endl;
        vector<string> v_gs_coeffs = DivideConstraints(gs_coeffs,"(C)");
        vector<string> v_x = DivideConstraints(variables,',');
        vector<string> v_d_x;
        for(int i = 0; i < v_x.size(); i++){
            v_d_x.push_back("d" + v_x[i]);
        }
        vector<string> f_coeff;
        string ret1,ret2;
        for(int i = 0; i < v_gs_coeffs.size(); i++){
            vector<string> v_gs_coe = DivideConstraints(v_gs_coeffs[i],' ');
            // PrintStringVector(v_gs_coe);
            if(v_gs_coe[v_gs_coe.size() - 1] == "P"){
                for(int j = 0; j < v_x.size(); j++){
                    ret1 += "+(" + v_gs_coe[j+3] + "/" + v_gs_coe[2] + "*" + v_x[j] +")";
                }
                // ret1 += ">=k" + to_string(cur_times) + ",";
                ret1 += ">=" + k +",";
                for(int j = 0; j < v_d_x.size(); j++){
                    ret2 += "+(" + v_gs_coe[j+3] + "/" + v_gs_coe[2] + "*" + v_d_x[j] +")";
                }
                ret2 += ">=0,";
            }
            if(v_gs_coe[v_gs_coe.size() - 1] == "R"){
                for(int j = 0; j < v_x.size(); j++){
                    ret1 += "+(" + v_gs_coe[j+3] + "*" + v_x[j] + ")";
                }
                ret1 += ">=0,";
                for(int j = 0; j < v_x.size(); j++){
                    ret2 += "+(" + v_gs_coe[j+3] + "*" + v_d_x[j] + ")";
                }
                ret2 += ">=0,";
            }
            if(v_gs_coe[v_gs_coe.size() - 1] == "L"){
                for(int j = 0; j < v_x.size(); j++){
                    ret1 += "+(" + v_gs_coe[j+3] + "*" + v_x[j] + ")";
                }
                ret1 += ">=0,";
                for(int j = 0; j < v_x.size(); j++){
                    ret1 += "-(" + v_gs_coe[j+3] + "*" + v_x[j] + ")";
                }
                ret1 += ">=0,";

                for(int j = 0; j < v_x.size(); j++){
                    ret2 += "+(" + v_gs_coe[j+3] + "*" + v_d_x[j] + ")";
                }
                ret2 += ">=0,";
                for(int j = 0; j < v_x.size(); j++){
                    ret2 += "-(" + v_gs_coe[j+3] + "*" + v_d_x[j] + ")";
                }
                ret2 += ">=0,";
            }
        }
        


        ret1.erase(ret1.size()-1);
        ret1 = "GS1 := {" + ret1 + "};";
        ret2.erase(ret2.size()-1);
        ret2 = "GS2 := {" + ret2 + "};";
        // std::cout<<"Start GS:"<<std::endl;
        return ret1+ret2;
    }
    
    vector<string> VectorPlus(vector<string> a,vector<string> b,int n){//a = a + n*b
        if(a[1] != b[1]){
            std::cout<<"Vector plus ERROR!"<<std::endl;
            return a;
        }
        int start = 2 ,len = stoi(a[1]), end = start + len;
        if(b[start] == "0"){
            b[start] = "1";
        }
        int mul_a = stoi(a[start]),mul_b = stoi(b[start]);
        for(int i = 0 ; i < len ; i++){
            a[start+i] = to_string( stoi(a[start+i]) * mul_b );
        }
        for(int i = 0 ; i < len ; i++){
            b[start+i] = to_string( stoi(b[start+i]) * mul_a );
        }
        for(int i = 1 ; i < len ; i++){
            a[start+i] = to_string( stoi(a[start+i]) + n*stoi(b[start+i]) );
        }
        return a;
    }

    bool isZeroVector(vector<string> a){
        int start = 2 , len = stoi(a[1]);
        for(int i = 1 ; i < len ; i++){
            if(a[start+i] != "0"){
                return false;
            }
        }
        return true;
    }

    
    string ConstructRandomEi(){
        srand((int)time(0));
        string ki = "ei := ";
        ki.append(std::to_string(rand()%10-5)+";");
        return ki;
    }
    
    /*
    if ret have only one resolution like {c1>=0,c2<=-1} then do nothing;
    if ret have several resolutions like {`or`(`and`(c1<0,c2>=-1),`and`(c1>=0,c2<=1))} then only return c1<0,c2>=-1 because ppl cannot handle several resolutions
    
     */
    string AnalyzeFarkasRet(string ret){
        int pos = 0;
        if((pos = ret.find("`&and`")) == string::npos){
            return ret;//only one ret,return
        }else{
            int pos1 = 0, pos2 = 0;
            pos2 = ret.find(")");
            pos1 = pos2 - 1;
            while(ret[pos1] != '('){
                pos1--;
            }
            return ret.substr(pos1 + 1, pos2 - pos1 - 1);
        }

        return ret;
    }


/*
    Construct [x,y,x0,y0,dx,dy,dx1,dy1] from [x,y]
    if k = -1 return x,y
    if k = 0 return x,y,x1,y1
    if k = 1 return x,y,x1,y1,dx,dy,dx1,dy1
 */
    string ConstructAllVariablesFromVariables(vector<string> variables,int k){
        vector<string> AllVariables;
        for(int i = 0 ; i < variables.size() ; i++){
            AllVariables.push_back(variables[i]);
        }
        if(k >= 0){
            for(int i = 0 ; i < variables.size() ; i++){
                AllVariables.push_back(variables[i]+"1");
            }
        }
        
        if(k >= 1){
            for(int i = 0 ; i < variables.size() ; i++){
                AllVariables.push_back("d"+variables[i]);
            }
            for(int i = 0 ; i < variables.size() ; i++){
                AllVariables.push_back("d"+variables[i]+"1");
            }
        }

        string ret;

        for(int i = 0; i < AllVariables.size(); i++){
            if(i != AllVariables.size()-1){
                ret += AllVariables[i] + ",";
            }else{
                ret += AllVariables[i];
            }
        }
        // std::cout<<ret<<std::endl;
        return ret;
    }

/*
    x = x - y => x1 = x - y
 */
    vector<string> ModifyVariables(vector<string> Cons, vector<string> variables){

        for(int i = 0 ; i < Cons.size() ; i++){
            for(int j = 0 ; j < Cons[i].length() ; j++){
                if(Cons[i][j] == '=') //only check variables of the left side of '='
                    break;

                for(int k = 0 ; k < variables.size() ; k++){
                    if(variables[k].length() == 1 && Cons[i][j] == variables[k][0]){
                        Cons[i].insert(j + 1 , "1");
                    }
                }    
            }
        }
        return Cons;
    }

/*
    construct x - x1 = dx
 */
    string ConstructDeltaPart1(vector<string> variables){
        string ret;
        for(int i = 0; i < variables.size(); i++){
            ret += variables[i] + "1 -" + variables[i] + " = d" + variables[i] + ","; 
        }
        return ret;
    }
/*
    construct A * dx + A1 * dx1 <= 0
 */
    string ConstructDeltaPart2(vector<string> Cons, vector<string> variables){

        for(int i = 0; i < Cons.size(); i++){
            //Cons[i] = Cons[i] + " ";
            //std::cout<<Cons[i]<<std::endl;
            bool tag1_sym = true, tag2_num = false;
            int start = 0;
            for(int j = 0; j < Cons[i].length(); j++){
                if(Cons[i][j] >= '0' && Cons[i][j] <= '9'){
                    tag2_num = true;
                    continue;
                }
                if(Cons[i][j] == '+' || Cons[i][j] == '-' ||
                 Cons[i][j] == '>' ||  Cons[i][j] == '<' ||
                  Cons[i][j] == '=' || j == Cons[i].length() - 1){
                      if(tag1_sym && tag2_num){
                          //std::cout<<"1:"<<j<<std::endl;
                          //std::cout<<start<<" "<<j<<std::endl;
                            Cons[i].replace(start, j - start, "0");
                           break;
                      }else if(tag1_sym){
                        //   tag = true;
                          start = j + 1;
                          //continue;
                        //   std::cout<<"2:"<<j<<std::endl;
                      }else if(tag2_num){
                          tag2_num = false;
                      }
                      tag1_sym = true;
                      start = j + 1;
                }else if(Cons[i][j] == '*' || Cons[i][j] == '/' || (Cons[i][j] >= 'a' && Cons[i][j] <= 'z') ||
                        (Cons[i][j] >= 'A' && Cons[i][j] <='Z') ){
                    tag1_sym = false;
                    // std::cout<<"3:"<<j<<std::endl;
                }
            }
        }
        for(int i = 0; i < Cons.size(); i++){
            for(int j = 0; j < variables.size(); j++){
                int pos1 = Cons[i].find(variables[j], 0);
                if(pos1 != -1){
                    Cons[i].insert(pos1, "d");
                }
                pos1 = Cons[i].find(variables[j], pos1 + 2);
                if(pos1 != -1){
                    Cons[i].insert(pos1, "d");
                }
            }
        }
        string ret;
        for(int i = 0; i < Cons.size(); i++){
            ret += Cons[i]+",";
        }
        
        return ret;        

    }

/*
    Omega: {A * x + A1 * x1 <= C} infer A, A1, C and construct Delat0
    Delat0: { x - x1 = dx, A * dx + A1 * dx1 <= 0, A * x + A1 * x1 <= C}
 */
    string ConstructDeltaFromCons(vector<string> LoopCons, vector<string> Cons, vector<string> variables){
        
        // string allvariables = ConstructAllVariablesFromVariables(variables);
        Cons = ModifyVariables(Cons,variables);
        
        //Omage = LoopCons + Cons

        string Delta;
        Delta += ConstructDeltaPart1(variables);
        Delta += ConstructDeltaPart2(Cons, variables);
        Delta += ConstructDeltaPart2(LoopCons, variables);
        Delta.erase(Delta.end() - 1);//delete end char','
        Delta = "Delta:={" + Delta + "};";
        // std::cout<<Delta<<std::endl;
        // for(int i = 0; i < LoopCons.size(); i++){
        //     std::cout<<LoopCons[i]<<std::endl;
        // }
        // for(int i = 0; i < Cons.size(); i++){
        //     std::cout<<Cons[i]<<std::endl;
        // }
        // for(int i = 0; i < variables.size(); i++){
        //     std::cout<<variables[i]<<std::endl;
        // }
        return Delta;
    }

    string ConstructOmega(vector<string> LoopCons, vector<string> Cons, vector<string> variables){
        string Omega;
        Cons = ModifyVariables(Cons,variables);
        for(int i = 0; i < LoopCons.size(); i++){
            Omega += LoopCons[i] + ",";
        }
        for(int i = 0; i < Cons.size(); i++){
            Omega += Cons[i] + ",";
        }
        Omega.erase(Omega.end() - 1);
        Omega = "Omega:={" + Omega + "};";
        // std::cout<<Omega<<std::endl;
        return Omega;
    }


}
#endif
