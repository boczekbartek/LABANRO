#include <iostream>
#include <ros/ros.h>
#include <kdl/joint.hpp>
#include <kdl/chain.hpp>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>

std::map <std::string, double> get_params();

using namespace KDL;
int main(int argc,  char** argv) {
    std::map <std::string,double> params /*= get_params()*/;
    params["a1"] = 0;
    params["a2"] = 0;
    params["d3"] = 0;
    params["theta1"] = 0;
    params["theta2"] = 0;

    if (argc !=1 ){
        int k = 1;
        for (std::map<std::string,double>::iterator i=params.begin(); i!=params.end(); i++){
            i->second = atof(argv[k]);
            k++;
            std::cout << i->first << " :" << i->second << std::endl;
        }
    }else {
        params["a1"] = 2;
        params["a2"] = 1;
        params["d3"] = 1;
        params["theta1"] = 3.14 / 8;
        params["theta2"] = 3.14 / 3;
    }
    Chain chain;
    Frame f1,f2,f3;
    f1 = Frame::DH(params.find("a1")->second,
                   0,
                   0,
                   params.find("theta1")->second);

    f2 = Frame::DH(params.find("a2")->second,
                   3.14,
                   0 ,
                   params.find("theta2")->second);

    f3 = Frame::DH(0,
                   0,
                   params.find("d3")->second,
                   0);

    chain.addSegment(Segment(Joint(Joint::RotZ),f1));
    chain.addSegment(Segment(Joint(Joint::RotZ),f2));
    chain.addSegment(Segment(Joint(Joint::RotZ),f3));

    int k=1;

    std::ofstream xacro_file;
    xacro_file.open("/home/bartek/Desktop/catkin_ws/src/lab02/urdf/xacro_file.xml");
    float x,y,z;
    for (std::vector<Segment>::iterator i = chain.segments.begin(); i != chain.segments.end(); ++i, ++k){
        double r=0,p=0,yy=0;
        i->getFrameToTip().M.GetRPY(r,p,yy);
        x = i->getFrameToTip().p.data[0];
        y = i->getFrameToTip().p.data[1];
        z = i->getFrameToTip().p.data[2];
        xacro_file << "<xacro:property name=\"r" <<k <<"\" value=\"" << r <<"\"/>\n";
        xacro_file << "<xacro:property name=\"p" <<k <<"\" value=\"" << p <<"\"/>\n";
        xacro_file << "<xacro:property name=\"yy" <<k <<"\" value=\"" << yy <<"\"/>\n";
        xacro_file << "<xacro:property name=\"x" <<k <<"\" value=\"" << x <<"\"/>\n";
        xacro_file << "<xacro:property name=\"y" <<k <<"\" value=\"" << y <<"\"/>\n";
        xacro_file << "<xacro:property name=\"z" <<k <<"\" value=\"" << z <<"\"/>\n";
        float l =  sqrt(x*x + y*y + z*z);
        xacro_file << "<xacro:property name=\"l" <<k <<"\" value=\"" << l<<"\"/>\n"; //dlugosc cylindra
        
        std::cout << "Segment " << k << std::endl;
        std::cout << "(r,p,y) : (" << r << "," << p << "," << yy << ")" << std::endl;
        std::cout << "(x,y,z) : (" << i->getFrameToTip().p.data[0] << "," << i->getFrameToTip().p.data[1]
                  << "," << i->getFrameToTip().p.data[2] << ")" << std::endl;
    }

    xacro_file.close();
    return 0;
}


std::map <std::string, double> get_params(){
    std::map <std::string, double> params;
    params["a1"] = 0;
    params["a2"] = 0;
    params["d3"] = 0;
    params["theta1"] = 0;
    params["theta2"] = 0;
    std::cout << "Enter dh parameters in order to convert to urdf:" << std::endl;

    for (std::map<std::string,double>::iterator i=params.begin(); i!=params.end(); i++){
        std::cout << i->first << std::endl;
        std::cin >> i->second;
    }
    return params;
}