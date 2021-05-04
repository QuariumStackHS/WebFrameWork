#include <FrameWork.hpp>
#include <fstream>
#include <sstream>
void*Smain(Backend*BE){
    ifstream i;
    i.open("templates/main.html");
    string Html;
    stringstream ik;
    cout<<"GonnaRead"<<endl;
    while(getline(i,Html)){
        ik<<Html;
    }
    
    //cout<<"read;"<<ik.str()<<endl;
    BE->Render_Html(ik.str());


}

int main(){
Backend*BE=new Backend();
BE->Register(&Smain,"/main");
BE->bind();

BE->Run();
BE->Run();
BE->Run();
}