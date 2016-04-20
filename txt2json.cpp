#include "txt2json.h"
#include "ui_txt2json.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <iostream>

using namespace std;

txt2json::txt2json(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::txt2json)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(generate()));
}

txt2json::~txt2json()
{
    delete ui;
}

txt2json::generate(){
    QString name=ui->lineEdit->text();
    QFile FileI(name+".txt");
    QFile FileO(name+".json");

    if(!FileI.open(QIODevice::ReadOnly | QIODevice::Text)){
        cout<<">Fail to open I"<<endl;
        return 0;
    }
    if(!FileO.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout<<">Fail to open O"<<endl;
        return 0;
    }
    QTextStream streamI(&FileI);
    QTextStream streamO(&FileO);


    QString line = streamI.readLine();

    streamO<<"{"<<endl;
    streamO<<"  \"description\" : \"\","<<endl;
    streamO<<"  \"encoding_version\" : \"0.1\","<<endl;
    streamO<<"  \"name\" : \""<<line<<"\","<<endl;
    streamO<<"  \"nodes\" : ["<<endl;

    vector<QString> listI;
    vector<QString> listO;
    int k=0;
    line = streamI.readLine();

    while(!streamI.atEnd()){
        listI.clear();
        listO.clear();
        cout<<line.toStdString()<<endl;
        name = streamI.readLine();
        cout<<name.toStdString()<<endl;
        line = streamI.readLine();
        cout<<line.toStdString()<<endl;
        while(line!=""){
            cout<<line.toStdString()<<endl;
            if(line.at(line.size()-1)=='i')
                listI.push_back(line);
            else
                listO.push_back(line);
            line = streamI.readLine();
        }
        if(k)
            streamO<<","<<endl;
        streamO<<"      {"<<endl;
        streamO<<"          \"cognitive_function\" : \"Attention\","<<endl;
        streamO<<"          \"name\" : \""<<name<<"\","<<endl;
        streamO<<"          \"ports\" : ["<<endl;

        for(int i=0;i<listI.size();i++){
            streamO<<"              {"<<endl;
            streamO<<"                  \"direction\" : \"in\","<<endl;
            streamO<<"                  \"name\" : \""<<listI[i]<<"\""<<endl;
            streamO<<"              }";
            if(i!=listI.size()-1||listO.size())
                streamO<<",";
            streamO<<endl;
        }
        for(int i=0;i<listO.size();i++){
            streamO<<"            {"<<endl;
            streamO<<"                  \"direction\" : \"out\","<<endl;
            streamO<<"                  \"name\" : \""<<listO[i]<<"\""<<endl;
            streamO<<"              }";
            if(i!=listO.size()-1)
                streamO<<",";
            streamO<<endl;

        }
        streamO<<"          ],"<<endl;
        streamO<<"      \"position\" : [ 604, -81 ],"<<endl;
        streamO<<"      \"uuid\" : \"1acc8787-72d6-4db3-a3d5-3770fbc7b4c"<<k<<"\""<<endl;
        streamO<<"  }";
        k++;
    }
    streamO<<endl;
    streamO<<"],"<<endl;
    streamO<<"\"uuid\" : \"43cf8ea5-42ed-47f2-a119-831410ae14f9\","<<endl;
    streamO<<"\"version\" : \"0.1\""<<endl;
    streamO<<"}"<<endl;
 }

