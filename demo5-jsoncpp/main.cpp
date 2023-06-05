#include <iostream> //读写io c++标准库
#include <fstream> //读写文件 c++标准库
#include <string> //字符串类 c++标准库
#include <sstream> //字符串流 c++标准库
#include "json/json.h" //jsoncpp的头文件

using namespace std;

void writeFileFromString(const string& filename,const string& body)
{
    ofstream ofile(filename);
    ofile<<body;
    ofile.close();
}

string readFileIntoString(const char * filename)
{
    ifstream ifile(filename);
    if(!ifile.is_open()){
        cerr<<"文件打开错误";
    }
    ostringstream buf;
    string filestr;
    char ch;
    while(buf && ifile.get(ch)){
        buf.put(ch);
    }
    filestr = buf.str();
    return filestr;
}

 Json::Value readJsonFile(const string & filename)
{
    //1.打开文件
    ifstream ifile;
    ifile.open(filename);
    
    //2.创建json读工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持，不加这句，utf8的中文字符会编程\uxxx
    
    //3.创建json对象，等会要返回这个对象
    Json::Value root;
    
    //4.把文件转变为json对象，要用到上面的三个变量,数据写入root
    string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder,ifile,&root,&strerr);
    if(!ok){
        cerr<<"json解析错误";
    }
    //5.返回存有数据的json，这个json对象已经能用了
    return root;
} 

Json::Value readJsonFromString(const string& mystr )
{
    //1.创建工厂对象
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;//utf8支持,不加这句,utf8的中文字符会编程\uxxx
    //2.通过工厂对象创建 json阅读器对象
    unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
    //3.创建json对象
    Json::Value root;
    //4.把字符串转变为json对象,数据写入root
    string strerr;
    bool isok = charread->parse(mystr.c_str(),mystr.c_str()+mystr.size(),&root,&strerr);
    if(!isok || strerr.size() != 0){
        cerr<<"json解析出错";
    }
    //5.返回有数据的json对象,这个json对象已经能用了
    return root;
}

void writeJsonFile(const string & filename,const Json::Value & root){
    //1.写json的工厂对象
    Json::StreamWriterBuilder writebuild;
    writebuild["emitUTF8"] = true;//utf8支持,加这句,utf8的中文字符会编程\uxxx
    //2.把json对象转变为字符串
    string document = Json::writeString(writebuild,root);
    //3.调用前面的写文件函数,写入文件
    writeFileFromString(filename,document);
}

int main(){
	string text = "JSON";
	std::cout << "Hello : " << text << std::endl;
	std::cout << "===========读json================" << std::endl;
	
	std::cout << "----------readJsonFile------------" << std::endl;
	//使用一个已经有数据的json对象
	Json::Value root;
	root = readJsonFile("../checkjson.json");
	//第一种使用方法get
	//使用get方法获取json对象的name的值,第二个参数是没有name时返回的值
	string name = root.get("name","null").asString();
	string phone_num = root.get("phone_number","null").asString();
	string car_num = root.get("car_number","null").asString();

	std::cout << "name: " << name << std::endl;
	std::cout << "phone_num: " << phone_num << std::endl;
	std::cout << "car_num: " << car_num << std::endl;
	//第二种使用方法root["name"],可以多级root["name"]["body"]
	
	
	std::cout << "----------readFileIntoString------------" << std::endl;
	
	string jsonText =  readFileIntoString("../checkjson.json");
	std::cout << "json : " << jsonText << std::endl;
	
	std::cout << "----------readJsonFromString--------------" << std::endl;
	
	Json::Value value = readJsonFromString(jsonText);
	name = root["name"].asString();
 	phone_num = root["phone_number"].asString();
	car_num = root["car_number"].asString();

	std::cout << "name: " << name << std::endl;
 	std::cout << "phone_num: " << phone_num << std::endl;
	std::cout << "car_num: " << car_num << std::endl;	 
	
	std::cout << "===========写json================" << std::endl;
	
	std::cout << "----------writeFileFromString--------------" << std::endl;
	writeFileFromString("../checkjson2.json",jsonText);
	std::cout << "写json完成: ../checkjson2.json" << std::endl;
	
	std::cout << "----------writeJsonFile--------------" << std::endl;
	writeJsonFile("../checkjson3.json",value);
	std::cout << "写json完成: ../checkjson3.json" << std::endl;
	
}