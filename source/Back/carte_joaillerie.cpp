#include "carte_joaillerie.h"

#include <iostream>

CarteJoaillerie::CarteJoaillerie(std::string line){
    //std::cout<<line<<'\n';
    std::istringstream iss(line);
            std::string token,token1;
            if(line[0]!='{' && line[0]!='}'){
                if (std::getline(iss, token, ';')) {
                    niveau=stoi(token);
                    //std::cout<<"  "<<token<<"\n";
                }
                if (std::getline(iss, token, ';')) {
                    pointsPrestige=stoi(token);
                    //std::cout<<"  "<<token<<"\n";
                }
                if (std::getline(iss, token, ';')) {
                    nombreBonus=stoi(token);
                    //std::cout<<"  "<<token<<"\n";
                }
                if (std::getline(iss, token, ';')) {
                    if(token=="blanc") typeBonus.set_Blanc(1);
                    if(token=="bleu") typeBonus.set_Bleu(1);
                    if(token=="vert") typeBonus.set_Vert(1);
                    if(token=="rouge") typeBonus.set_Rouge(1);
                    if(token=="noir") {typeBonus.set_Noir(1);}
                    if(token=="perle") typeBonus.set_Perle(1);
                    //std::cout<<"  "<<token<<"\n";
                }
                if (std::getline(iss, token, ';')) {
                    couronnes=stoi(token);
                    //std::cout<<token<<"\n";
                }
                if (std::getline(iss, token, ';')) {
                    std::istringstream iss1(token);
                    //std::cout<<"\n->"<<token<<"<-\n";
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Blanc(stoi(token1));
                        //std::cout<<"\n->"<<token1<<"<-\n";
                    }
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Bleu(stoi(token1));
                    }
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Vert(stoi(token1));
                    }
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Rouge(stoi(token1));
                    }
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Noir(stoi(token1));
                    }
                    if (std::getline(iss1, token1, ',')) {
                        cout.set_Perle(stoi(token1));
                    }
                    //std::cout<<"       cout :"<<tempcout<<std::endl;
                }
                if (std::getline(iss, token, ';')) {
                //std::cout<<"    capacite :";
                    std::istringstream iss1(token);

                    while (std::getline(iss1, token1, ',')) {
                        if(token1=="rejouer") capacite.push_back(Effet(0));
                        if(token1=="voler") capacite.push_back(Effet(4));
                        if(token1=="privilege") capacite.push_back(Effet(1));;
                        if(token1=="couleur") capacite.push_back(Effet(2));
                        if(token1=="gemme") capacite.push_back(Effet(3));
                        if(token1=="sans") capacite.push_back(Effet(5));
                    }
                   
                }
                if(std::getline(iss,token,';')){
                    cheminImage=token;
                }
            }
}