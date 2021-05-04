#include <FrameWork.hpp>
#include <unistd.h>
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }
    

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}
Backend::Backend(){
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}
int Backend::Register(void *(Func)(Backend *),string PRoute){

Route *newRoute=new Route(Func,PRoute);

this->Routes.push_back(newRoute);
}
Backend::Route::Route(void *(FuncN)(Backend *), string RouteN){
this->Func=FuncN;
this->RouteName=RouteN;
};
int Backend::Run(){

        //cout << "rcv data" << endl;
        char bufferd[1024]={0};
        valread = read(new_socket, &bufferd, 1024);
        cout<<bufferd<<endl;
        vector<string>Args;
        //cout<<(string)bufferd<<endl;
        split((string)bufferd,Args,' ');
        //cout<<this->Routes.size()<<Args[1]<<endl;'
        cout<<Args[3]<<" | "<<Args[0]<<" "<<Args[1]<<" | "<<Args[17]<<endl;
        int found=0;
        for(int i=0;i<this->Routes.size();i++){
            //cout<<this->Routes[i]->RouteName<<endl;
            if(strcmp(this->Routes[i]->RouteName.c_str(),Args[1].c_str())==0){
                this->Routes[i]->Func(this);
                //cout<<"found"<<endl;
                found=1;
            }
        }
        if (found==0){
            this->Render_Html("<HTML>404 Not Found</HTML>");
        }
        else{
        cout<<".."<<endl;
        }
        
}
int Backend::bind()
    {
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 80
        if (::bind(server_fd, (struct sockaddr *)&address,
                   sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
            if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        cout << "end;" << endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
    }
int Backend::Render_Html(string Html){
    string Header="HTTP/1.0 200 OK"\
"Date: Fri, 31 Dec 1999 23:59:59 GMT"\
"Server: Reltt/0.0.1"\
"Content-Type: text/html"\
"Content-Length: 59"\
"Expires: Sat, 01 Jan 2021 00:59:59 GMT"\
"Last-modified: Fri, 09 Aug 2021 14:21:40 GMT";


    send(new_socket, (Header+Html).c_str(), strlen((Header+Html).c_str()), 0);
    cout<<"oof"<<endl;
}