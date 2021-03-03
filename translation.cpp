#include<bits/stdc++.h>
#include<windows.h>
#include<io.h>
#include<fstream>
using namespace std;

const int Mxn=1e5+5;
#define ll long long int
#define pb push_back
#define mk make_pair
std::wstring Utf82Unicode(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		// throw std::exception("Invalid UTF-8 sequence.");
    }
	if (widesize == 0)
	{
		// throw std::exception("Error in conversion.");
	}
 
	std::vector<wchar_t> resultstring(widesize);
 
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
 
	if (convresult != widesize)
	{
		// throw std::exception("La falla!");
	}
 
	return std::wstring(&resultstring[0]);
}
 
 
//unicode 转为 ascii
 
 
std::string WideByte2Acsi(std::wstring& wstrcode)
{
	int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		// throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		// throw std::exception("Error in conversion.");
	}
    std::vector<char> resultstring(asciisize);
	int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
 
	if (convresult != asciisize)
	{
		// throw std::exception("La falla!");
	}
 
    return std::string(&resultstring[0]);
}
 
 
 
 
 
//utf-8 转 ascii
 
 
std::string UTF_82ASCII(std::string& strUtf8Code)
{
	std::string strRet("");
	//先把 utf8 转为 unicode
	std::wstring wstr = Utf82Unicode(strUtf8Code);
	//最后把 unicode 转为 ascii
	strRet = WideByte2Acsi(wstr);
	return strRet;
}
 
 
///
 
 
//ascii 转 Unicode
 
 
std::wstring Acsi2WideByte(std::string& strascii)
{
	int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		// throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		// throw std::exception("Error in conversion.");
	}
    std::vector<wchar_t> resultstring(widesize);
	int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
 
 
	if (convresult != widesize)
	{
		// throw std::exception("La falla!");
	}
 
    return std::wstring(&resultstring[0]);
}
 
 
//Unicode 转 Utf8
 
 
std::string Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		// throw std::exception("Error in conversion.");
	}
 
	std::vector<char> resultstring(utf8size);
 
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
 
	if (convresult != utf8size)
	{
		// throw std::exception("La falla!");
	}
 
	return std::string(&resultstring[0]);
}
 
 
//ascii 转 Utf8
 
 
std::string ASCII2UTF_8(std::string& strAsciiCode)
{
	std::string strRet("");
	//先把 ascii 转为 unicode
	std::wstring wstr = Acsi2WideByte(strAsciiCode);
	//最后把 unicode 转为 utf8
	strRet = Unicode2Utf8(wstr);
	return strRet;
}

void changecoding(string dir,string f){ //translate coding
    _finddata_t file;
    string dir2=dir+"\\*";
    long handle=_findfirst(dir2.c_str(),&file);
    if(handle==-1){
        cout<<"no such folder path"<<endl;
    }
    else{
        do{
            if(file.attrib & _A_SUBDIR){ //have folder
                
                if((strcmp(file.name,".")!=0)&& (strcmp(file.name,"..")!=0)){
                    string newdir=dir+"\\"+file.name;
                    changecoding(newdir,f);
                }
            }
            else{
                int size=0;
                int t=0;
                while(file.name[t]){
                    size++;
                    t++;
                }
                bool flag=false;
                for(int i=0;i<f.size();i++){
                    if(size-f.size()+i<0) break;
                    if(file.name[size-f.size()+i]!=f[i]){
                        flag=true;
                    }
                }
                if(flag==false){ //match extension
                    fstream f1,f2;
                    char buffer[200];
                    f1.open("tmp.txt",ios::out);
                    string s2=dir+"\\"+file.name;
                    f2.open(s2.c_str(),ios::in);
                    do{
                        f2.getline(buffer,sizeof(buffer));
                        string s=buffer;
                        f1<<ASCII2UTF_8(s)<<endl;  //ascii to utf8
                    }while(!f2.eof());
                    f1.close();
                    f2.close();
                    f1.open(s2.c_str(),ios::out);
                    f2.open("tmp.txt",ios::in);
                    do{
                        f2.getline(buffer,sizeof(buffer));
                        string s=buffer;
                        f1<<s<<endl;
                    }while(!f2.eof());
                    f1.close();
                    f2.close();
                }
            }
        }while(_findnext(handle,&file)==0); 
    }
    _findclose(handle);
}
void showfile(string dir,int empty){ //list all files
    _finddata_t file;
    string dir2=dir+"\\*";
    long handle=_findfirst(dir2.c_str(),&file);
    if(handle==-1){
        cout<<"no such folder path"<<endl;
    }
    else{
        do{
            for(int i=0;i<empty;i++){
                cout<<"    ";
            }
            cout<<file.name<<endl;
            if(file.attrib & _A_SUBDIR){ //have folder
                
                if((strcmp(file.name,".")!=0)&& (strcmp(file.name,"..")!=0)){
                    string newdir=dir+"\\"+file.name;
                    showfile(newdir,empty+1);
                }
            }
        }while(_findnext(handle,&file)==0); 
    }
    _findclose(handle);
}
int main(){
    ios_base::sync_with_stdio(0);  cin.tie(0);
    string dir="C:\\Users\\邱以中\\Desktop\\test";
    int t;
    cout<<"1.list the files 2.translate the coding"<<endl;
    cin>>t;
    if(t==1){
        showfile(dir,0);
    }
    else{
        string f;
        cout<<"file extension"<<endl;
        cin>>f;
        changecoding(dir,f);
    }

}