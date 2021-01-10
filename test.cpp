#include<string>
#include<bits/stdc++.h>
using namespace std;
template<class Key,
    class Ty,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Alloc = std::allocator<std::pair<const Key, Ty> > >
    class unordered_map;
    > class unordered_map
struct Token{
	string cifadanyuan;
	string cisu;
	Token(){
	}
	Token(string cifadanyuan,string cisu){
		this->cifadanyuan = cifadanyuan;
		this->cisu = cisu;
	}
	string toString(){
		return this->cifadanyuan+"  "+this->cisu;
	}
	//toString�������������Ǻ������չʾ������̨��
};
class Lexical{
	const string operators = "+-*/%=&|<>!";
	const string singleword = "(),.;";
	//����ʹ��һ����ϣ�����洢sql����ı����֣�����ֻ��һ���֣������Ŀ��ԵĻ�������ȫ�ӽ�ȥ��
	unordered_map<string,int> keyword{
					{"select",1},{"insert",2},{"delete",3},{"update",4},
					{"from",5},{"create",6},{"database",7},{"as",8},
					{"drop",9},{"alter",10},{"into",11},{"where",12},
					{"join",13},{"set",14},{"use",15},{"table",16},
					{"index",17},{"primary",18},{"in",19},{"between",20},
					{"like",21},{"and",22},{"or",23},{"key",24},
					{"by",25},{"character",26},{"varchar",25},{"boolean",26},
					{"int",25},{"decimal",26},{"null",25},{"date",26},
					{"time",25},{"not",26},{"values",27},{"order",28}
				};
	char temp[40];//���������Ƿ�������token���ȷ���һ����ʱ��������
	char *ch;//��������ָ������������ָ�롣

	Token lexOperators(){...} //����������ĺ�����˳���̵�ע��
	Token lexIdentifier(){...}//���������ֺ��û��Զ����ʶ���ĺ���
	Token lexDigit(){...}//����������С���ĺ���
	Token lexString(){...}//�����ַ����ĺ���
	Token lexSingleword(){...}//�������ţ��ֺŵȵȵĺ���
	Lexical(char* ch){ this->ch = ch; } //�������Ĺ��캯��
	vector<Token> lexSource(){...}//��������������������sql���
}
Token lexOperators(){
		Token token;
		if(*ch == '/'){
			switch(*(++ch)){
				case '*':
					while((*ch != '/' || *(ch - 1) != '*') && *ch != '\0') ch++;
					break;
				default:
					temp[0] = *(--ch);
					temp[1] = '\0';
					token.cifadanyuan = temp;
					token.cisu = temp;
			}
		}else if(*ch == '<' || *ch == '>' || *ch == '!'){
			if(*(ch + 1) == '='){
				temp[0] = *ch;
				temp[1] = *(++ch);
				temp[2] = '\0';
			}else{
				temp[0] = *ch;
				temp[1] = '\0';
			}
			token.cifadanyuan = temp;
			token.cisu = temp;
		}else{
			temp[0] = *ch;
			temp[1] = '\0';
			token.cifadanyuan = temp;
			token.cisu = temp;
		}
		ch++;
		return token;
}
Token lexIdentifier(){
		Token token;
		int i;
		for(i = 0;isalpha(*ch);ch++) {
			temp[i++] = *ch;
		}
		temp[i] = '\0';
		string s = (string)temp;
		transform(s.begin(), s.end(), s.begin(),::tolower);
		if(keyword.find(s) != keyword.end()){
			token.cifadanyuan = s;
			token.cisu = s;
		}else{
			token.cifadanyuan = "ID";
			token.cisu = temp;
		}
		return token;
}
Token lexDigit(){
		int i;
		int flag = 1;
		Token token;
		for(i = 0; isdigit(*ch) || *ch == '.'; ch++){
			if(*ch == '.'){
				if(flag){ flag = 0;	} else { break; }
			}
			temp[i++] = *ch;
		}
		temp[i] = '\0';
		token.cifadanyuan = "NUM";
		token.cisu = temp;
		return token;
}
Token lexString(){
		Token token;
		int i;
		for(i = 0,ch++; *ch != '\'' && *ch != '\0'; ch++){
			temp[i++] = *ch;
		}
		temp[i] = '\0';
		token.cifadanyuan = "STRING";
		token.cisu = temp;
		ch++;
		return token;
}
Token lexSingleword(){
		temp[0] = *(ch++);
		temp[1] = '\0';
		Token token(temp,temp);
		return token;
}
vector<Token> lexSource(){
		vector<Token> result;
		while(*ch != '\0'){
			while(isspace(*ch)) ch++;
			if(isalpha(*ch)) {
				result.push_back(lexIdentifier());
			}else if(isdigit(*ch)) {
				result.push_back(lexDigit());
			}else if(operators.find(*ch) != string::npos) {
				result.push_back(lexOperators());
			}else if(*ch =='\'') {
				result.push_back(lexString());
			}else if(singleword.find(*ch) != string::npos) {
				result.push_back(lexSingleword());
			}
		}
		return result;
}
int main(){
	fstream source("test.cpp");
	istreambuf_iterator<char> beg(source), end;
	string buffer(beg, end);
	char* ch = (char*)buffer.c_str();
	Lexical lex(ch);
	vector<Token> s = lex.lexSource();
	Token t;
	for(int i = 0; i < s.size(); i++){
		t = s[i];
		cout<<t.toString()<<"\n";
	}
	source.close();
	return 0;
}













