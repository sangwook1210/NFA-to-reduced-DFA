# NFA-to-reduced-DFA

vector<string> tokenize(string s) {	//문자열 s를 띄어쓰기를 기준으로 토큰화하여 반환하는 함수
	size_t pos = 0;	//pos를 0으로 초기화
	string delim = " ";	//띄어쓰기
	vector<string> token;	//s를 띄어쓰기를 기준으로 토큰화한 것을 저장할 벡터
	token.clear();

	while ((pos = s.find(delim)) != string::npos) {	//s에 여러 개의 상태들이 들어있다면 
		token.push_back(s.substr(0, pos));	//띄어쓰기를 기준으로 토큰화하여 token에 저장한다
		s.erase(0, pos + delim.length());
	}
	token.push_back(s);	//s에 한 개의 상태가 들어있거나 여러 개의 상태들이 들어있을 때의 마지막 상태를 token에 저장한다

	return token;
}
위 tokenize 함수는 string s에 저장되어 있는 문자열을 띄어쓰기를 기준으로 잘라 token 벡터에 각각 저장하여 이를 반환하는 함수입니다.
