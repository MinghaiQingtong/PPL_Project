/* Some functions for maple programming with C++ by Tangtong
 * 2019/9/7
 */

#ifndef _TangtongFunctions_H
#define _TangtongFunctions_H

#include <maplec.h>
#include <TangtongPPL_header_c.cpp>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

namespace TangtongMaple{


    /*
        Construct Maple statement.
        Convert string Maple order statement to valid statement.
        And there is a default order statement calling "x = 1; y = 2; x + y;".
     */

    bool ConstructMapleStatement(char *ch){
        // string str = "F:=proc(x,y) return x+y end:";
        string str = "x = 1; y = 2; x + y;";
        strcpy(ch,str.c_str());
        return true;
    }

    bool ConstructMapleStatement(char *ch,string str){
        strcpy(ch,str.c_str());
        return true;
    }

    /*
        Construct adding Maple Lib statement.
        The default libs are ArrayTools,linalg,simplex,RegularChains,SemiAlgebraicSetTools.
     */

    bool ConstructRelLibStatement(char *ch){
        string str = "with(ArrayTools): \
                    with(linalg): \
                    with(simplex): \
                    with(RegularChains): \
                    with(SemiAlgebraicSetTools):";
        strcpy(ch,str.c_str());
        return true;
    }
    bool ConstructRelLibStatement(char *ch,string str){
        strcpy(ch,str.c_str());
        return true;
    }

    // bool ConstructOmega(string gs_coeffs,string x){
        
    //     return true;
    // }

    /*
        Construct Farkas function statement to maple system.
        There are two Farkas functions for different use.
        The firse one is to calculate xxxxxxx.
        The second one is to calculate xxxxxx.
     */
    bool ConstructFirstFarkasStatement(char *ch){
        string str = " Farkas:=proc(S_ineqns,x) \
        local i,temp,temp2,S_eqnsMatrix,S_vector,C_vector,eqns,lambda,f;\
        S_eqnsMatrix:={};\
        for i from 1 to nops(S_ineqns) do\
            temp:=convert(S_ineqns[i],equality);\
            S_eqnsMatrix:=`union`(S_eqnsMatrix,{temp});\
        od;\
        S_eqnsMatrix,S_vector:=LinearAlgebra:-GenerateMatrix(S_eqnsMatrix,x);\
        S_eqnsMatrix:=LinearAlgebra:-Transpose(LinearAlgebra:-Multiply(S_eqnsMatrix,-1));\
        temp:=Array([seq(-c[i],i=1..nops(x)/2)]);\
        temp:=ArrayTools:-Extend(temp,[seq(c[i],i=1..nops(x)/2)]);\
        C_vector:=Vector(nops(x),temp);\
        lambda:=[seq(lambda[i],i=1..nops(S_ineqns))];\
        eqns:=LinearAlgebra:-GenerateEquations(S_eqnsMatrix,lambda,C_vector);\
        S_vector:=convert(S_vector,list);\
        S_vector:=matrix(1,nops(S_ineqns),S_vector);\
        temp:=convert(linalg:-geneqns(S_vector,lambda,convert([-1],vector))[1],lessequal);\
        eqns:=`union`({temp},convert(eqns,set));\
        temp:=0;\
        for i from 1 to nops(S_ineqns) do\
           temp:=temp+lambda[i];\
        od;\
        temp:={temp>=1};\
        \
        for i from 1 to nops(S_ineqns) do\
            temp:={lambda[i]>=0};\
            eqns:=`union`(temp,eqns);\
        od;\
        eqns:=convert(eqns,list);\
        temp:=[seq(lambda[i],i=1..nops(S_ineqns))];\
        temp:=[op(temp),op([seq(c[i],i=1..1/2*nops(x))])];\
        temp:=RegularChains:-SemiAlgebraicSetTools:-LinearSolve(eqns,RegularChains:-PolynomialRing(temp),'projection'=1/2*nops(x));\
        return convert(temp,set);\
        end proc;\
        ";
        strcpy(ch,str.c_str());
        return true;
        /*
        temp2 := `&and`(seq(eqns[i], i = 1 .. nops(eqns)));\
        f:=`&E`(temp),temp2;\
        print(f);\
        temp := RegularChains:-SemiAlgebraicSetTools:-QuantifierElimination(f, output = rootof, simplification = L4);\
 
 */
        }


    bool processMapleStatement(MKernelVector &kv,char *maplestatement,string MapleOrder){
        ConstructMapleStatement(maplestatement,MapleOrder);
        EvalMapleStatement(kv,maplestatement);
        return true;
    }
    bool processFirstFarkasStatement(MKernelVector &kv,char *maplestatement){
        TangtongMaple::ConstructFirstFarkasStatement(maplestatement);
        EvalMapleStatement(kv,maplestatement);
        return true;
    }


}


#endif
