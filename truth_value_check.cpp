#include<iostream>
#include<string>

using namespace std;

bool dealVal(string& subStr,string& val);
size_t findIt(string& subStr,size_t beginPos);

int main()
{
	string checkStr;
	cin>>checkStr;
	string val;
	cin>>val;

	bool out=dealVal(checkStr,val);
	cout<<boolalpha<<out<<endl;

	return 0;
}

bool dealVal(string& subStr,string& val)
{
	auto beginPos=subStr.find('(');
	auto endPos=findIt(subStr,beginPos);
	bool boolVal=true,temp=true;

	while(beginPos!=string::npos)
	{
		auto newStr=subStr.substr(beginPos+1,endPos-beginPos-1);
		temp=dealVal(newStr,val);
		if(beginPos==0)
			boolVal=temp;
		else
		{
			switch(subStr[beginPos-1])
			{
			case '!':
				temp=!temp;
				if(beginPos>1)
				{
					switch(subStr[beginPos-2])
					{
					case '|':
						boolVal=(boolVal||temp);
						break;
					case '&':
						boolVal=(boolVal&&temp);
						break;
					default:
						break;
					}
				}
				else
					boolVal=temp;
				break;
			case '|':
				boolVal=(boolVal||temp);
				break;
			case '&':
				boolVal=(boolVal&&temp);
				break;
			default:
				boolVal=temp;
				break;
			}
		}
		beginPos=subStr.find('(',endPos);
		endPos=findIt(subStr,beginPos);
	}

	size_t num;
	if(endPos==string::npos)
		num=0;
	else
		num=endPos+1;
	while(num<subStr.length())
	{
		if(subStr[num]=='p')//如果是命题
		{
			auto iPos=atoi(subStr.substr(num+1).c_str());
			if(num==0)
			{
				boolVal=static_cast<bool>(val[iPos]-'0');
				temp=static_cast<bool>(val[iPos]-'0');
			}
			else
			{
				temp=static_cast<bool>(val[iPos]-'0');
				switch(subStr[num-1])
				{
				case '!':
					temp=!temp;
					if(num>1)
					{
						switch(subStr[num-2])
						{
						case '|':
							boolVal=(boolVal||temp);
						case '&':
							boolVal=(boolVal&&temp);
						default:
							break;
						}
					}
					else
						boolVal=temp;
					break;
				case '|':
					boolVal=(boolVal||temp);
					break;
				case '&':
					boolVal=(boolVal&&temp);
					break;
				default:
					break;
				}
			}
		}
		++num;
	}
	return boolVal;
}

size_t findIt(string& subStr,size_t beginPos)
{
	int count=0;
	auto endPos=subStr.find(')',beginPos);
	auto findPos=subStr.find('(',beginPos+1);
	while(findPos!=string::npos&&findPos<endPos)
	{
		findPos=subStr.find('(',findPos+1);
		++count;
	}

	--count;
	while(count>0)
	{
		endPos=subStr.find(')',endPos+1);
		--count;
	}

	return endPos;
}
