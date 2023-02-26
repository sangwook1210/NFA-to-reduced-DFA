# NFA-to-reduced-DFA

vector\<string\> tokenize(string s) { //문자열 s를 띄어쓰기를 기준으로 토큰화하여 반환하는 함수

size\_t pos = 0; //pos를 0으로 초기화

string delim = " "; //띄어쓰기

vector\<string\> token; //s를 띄어쓰기를 기준으로 토큰화한 것을 저장할 벡터

token.clear();

while ((pos = s.find(delim)) != string::npos) { //s에 여러 개의 상태들이 들어있다면

token.push\_back(s.substr(0, pos)); //띄어쓰기를 기준으로 토큰화하여 token에 저장한다

s.erase(0, pos + delim.length());

}

token.push\_back(s); //s에 한 개의 상태가 들어있거나 여러 개의 상태들이 들어있을 때의 마지막 상태를 token에 저장한다

return token;

}

위 tokenize 함수는 string s에 저장되어 있는 문자열을 띄어쓰기를 기준으로 잘라 token 벡터에 각각 저장하여 이를 반환하는 함수입니다.

string combine(vector\<string\> a, vector\<string\> state) { //vector a에 담긴 문자열들을 하나로 합쳐 반환하는 함수

string s;

int cnt = 0;

//벡터 a에 저장되어 있는 값들을 string s에 합칠 때, 순서대로 합치기 위해서 이중 for문을 사용한다.

for (int i = 0; i \< state.size(); i++) {

for (int j = 0; j \< a.size(); j++) {

if (a[j].find(state[i]) != string::npos) {

if (cnt == 0) { //s에 제일 처음으로 저장할 경우

s.assign(a[j]);

cnt++;

}

else {

s.append(" ");

s.append(a[j]);

}

}

}

}

return s;

}

위 combine 함수는 벡터 a에 각각 저장되어 있는 상태들을 하나의 문자열로 합치는 함수입니다.
합치는 과정에서 i를 0부터 오름차순으로 증가시키고 a[j]에 state[i]가 있는지 확인하여 있으면 문자열 s에 저장합니다. 이를 통하여 state에 저장되어 있는 상태의 순서대로 합칩니다.

//DFA의 시작 상태를 DFA.state에 저장하고 시작 상태의 다음 상태를 DFA.next\_state와 중복이 되지 않는다면 DFA.state에 저장

for (i = 0; i \< NFA.state.size(); i++) { //NFA의 상태의 개수만큼 반복

if (NFA.start\_state.compare(NFA.state[i]) == 0) { //NFA의 시작 상태가 NFA.state[i]라면

DFA.state.push\_back(NFA.state[i]); //DFA의 첫 번째 상태로 NFA.state[i]를 집어넣는다

for (j = 0; j \< DFA.input.size(); j++) { //DFA의 input의 개수만큼 반복

cnt = 0; //cnt를 0으로 설정

for (k = 0; k \< DFA.state.size(); k++) { //DFA의 상태의 개수만큼 반복

if (NFA.next\_state[i \* DFA.input.size() + j].compare(DFA.state[k]) != 0) { //NFA의 시작 상태의 다음 상태들이 DFA의 상태들과 겹치지 않는다면

cnt++; //cnt를 1 증가시킨다

}

}

if (cnt == DFA.state.size()) { //cnt가 DFA의 상태의 개수와 같아져 중복이 없음이 확인되었다면

DFA.state.push\_back(NFA.next\_state[i \* DFA.input.size() + j]); //DFA\_state에 NFA의 시작 상태의 다음 상태들을 추가한다

}

DFA.next\_state.push\_back(NFA.next\_state[i \* DFA.input.size() + j]); //DFA의 시작 상태의 다음 상태들에 NFA의 시작 상태의 다음 상태들을 추가한다

}

break;

}

}

위 코드는 입력받은 NFA가 epsilon-NFA가 아닐 경우, NFA의 시작 상태를 DFA의 첫 번째 상태로 집어넣고 그 첫 번째 상태의 각각의 입력 심벌에 대한 다음 상태를 다음 상태들을 모아놓는 DFA.next\_state에 저장하고, 그 저장된 상태들을 중복이 되지 않는다면 DFA.state에 저장하는 코드입니다.

위 과정을 거치면 DFA의 시작 상태는 DFA.state[0]에 저장되고, 시작 상태의 i번째 입력 심벌인 DFA.input[i]에 대한 다음 상태는 DFA.next\_state[0\*input.size()+i]에 저장이 됩니다.

//DFA의 시작 상태를 제외한 다른 DFA.state들의 각 입력 심벌에 따른 다음 상태를 DFA.next\_state와 중복이 되지 않는다면 DFA.state에 저장

for (i = 1; i \< DFA.state.size(); i++) { //DFA의 시작 상태의 다음 상태들은 이미 DFA.next\_state에 저장해 두었으므로 i=0인 시작 상태를 제외하고 i=1부터 시작

tmp\_DFA.clear(); //tmp\_DFA 벡터를 초기화한다

tmp.assign(DFA.state[i]); //tmp에 DFA\_state[i]를 임시로 저장해둔다

tmp\_DFA = tokenize(tmp); //tmp\_DFA에 tmp를 tokenize한 것을 저장해둔다

if (tmp\_DFA.size() == 1) { //만약 DFA.state[i]가 한 개의 상태라면

for (j = 0; j \< NFA.state.size(); j++) { //NFA의 상태의 개수만큼 반복

if (tmp\_DFA[0].compare(NFA.state[j]) == 0) { //tmp\_DFA와 같은 상태를 state에서 찾아

cnt = 0; //cnt를 0으로 설정

for (k = 0; k \< DFA.input.size(); k++) { //DFA의 입력 심볼의 개수만큼 반복

DFA.next\_state.push\_back(NFA.next\_state[j \* DFA.input.size() + k]); //DFA.next\_state에 현재 NFA.state[j]의 next state를 추가한다

for (l = 0; l \< DFA.state.size(); l++) { //모든 DFA.state[]를 비교하기 위하여 DFA.state.size()만큼 반복

if (DFA.state[l].compare(NFA.next\_state[j \* DFA.input.size() + k]) != 0) { //위에서 DFA.next\_state에 추가된 것들이 DFA\_state[l]과 중복되지 않는다면

cnt++; //cnt를 1 증가시킨다

}

}

if (cnt == DFA.state.size()) { //만약 cnt가 DFA\_state.size()와 같아져 중복이 없음이 확인되었다면

DFA.state.push\_back(NFA.next\_state[j \* DFA.input.size() + k]); //DFA\_state에 위에서 DFA.next\_state에 추가된 것들을 추가한다

}

}

}

}

}

else { //만약 DFA.state[i]가 여러 개의 상태라면

for (a = 0; a \< DFA.input.size(); a++) { //DFA의 입력 심벌의 개수만큼 반복

tmp\_next1.clear(); //tmp\_next1 벡터를 초기화한다

tmp\_next2.clear(); //tmp\_next2 벡터를 초기화한다

//분리된 DFA의 다음 상태 저장하기

for (j = 0; j \< tmp\_DFA.size(); j++) { //DFA.state[i]에 저장되어 있는 상태의 개수만큼 반복

for (k = 0; k \< NFA.state.size(); k++) { //NFA의 상태의 개수만큼 반복

if (tmp\_DFA[j].compare(NFA.state[k]) == 0) { //state[i]의 분리된 상태가 NFA.state[k]와 일치한다면

tmp\_next1.push\_back(NFA.next\_state[k \* DFA.input.size() + a]); //NFA.state[k]의 a번째 입력 심볼에 대한 다음 상태를 tmp\_next1에 저장

}

}

}

for (j = 0; j \< NFA.state.size(); j++) { //순서대로 나열하기 위해 NFA.state의 j를 0부터 증가시킨다

cnt = 0; //중복 제거를 위한 cnt

for (k = 0; k \< tmp\_next1.size(); k++) { //tmp\_next1의 크기만큼 반복

if ((tmp\_next1[k].find(NFA.state[j]) != string::npos) && cnt == 0) { //tmp\_next1[k]에 NFA.state[j]가 존재하고 cnt의 값이 0이라면

tmp\_next2.push\_back(NFA.state[j]); //NFA.state[j] 값을 tmp\_next2에 추가한다

cnt++; //중복된 값을 tmp\_next2에 추가하지 않기 위하여 cnt를 1 증가시킨다

}

}

}

//tmp\_next2에 저장된 값들을 tmp에 합쳐 저장한다

tmp.assign(combine(tmp\_next2));

//tmp의 값이 DFA의 상태들과 중복되지 않는다면

cnt = 0;

for (j = 0; j \< DFA.state.size(); j++) { //tmp의 값이 DFA의 상태들과 중복되는지 검사

if (tmp.compare(DFA.state[j]) != 0) {

cnt++;

}

}

if (cnt == DFA.state.size()) { //tmp의 값이 DFA의 상태들과 중복되지 않는다면

DFA.state.push\_back(tmp); //DFA.state에 tmp 삽입

}

DFA.next\_state.push\_back(tmp); //DFA.next\_state에 tmp 삽입

}

}

}

위 코드는 DFA의 시작 상태의 각 입력 심벌에 따른 다음 상태들을 중복이 되지 않는다면 DFA의 상태에 추가하였을 때, 이 추가된 상태들의 각 입력 심벌에 따른 다음 상태들을 DFA.next\_state에 저장하고, 이 상태들이 DFA.state에 저장되어 있는 상태들과 중복되지 않는다면 이들을 DFA.state에 새롭게 추가하는 코드입니다.

위 과정을 거치면 DFA의 i번째 상태인 DFA.state[i]의 j번째 입력 심벌인 DFA.input[j]에 대한 다음 상태는 DFA.next\_state[i\*input.size()+j]가 됩니다.

void epsilon\_closure(vector\<string\> state, vector\<string\> next\_state\_ep, string s, vector\<string\>& tmp\_ep) { //epsilon\_closure 함수

vector\<string\> tmp\_ep\_closure; //s를 토큰화하여 저장할 변수

tmp\_ep\_closure = tokenize(s); //s를 토큰화하여 tmp\_ep\_closure에 저장한다

for (int i = 0; i \< tmp\_ep\_closure.size(); i++) { //tmp\_ep\_closure에 담긴 상태의 개수만큼 반복

int cnt = 0; //cnt를 0으로 설정

for (int a = 0; a \< tmp\_ep.size(); a++) { //tmp\_ep의 크기만큼 반복

if (tmp\_ep\_closure[i].compare(tmp\_ep[a]) == 0) { //만약 tmp\_ep\_closure[i]와 tmp\_ep[a]가 같으면

cnt++; //cnt를 1 증가시킨다

}

}

if (cnt == 0) { //tmp\_ep\_closure[i]와 tmp\_ep[a]가 같음이 발견되지 않아 cnt가 증가되지 않았다면 중복이 없다는 뜻이므로

tmp\_ep.push\_back(tmp\_ep\_closure[i]); //tmp\_ep\_closure[i]를 tmp\_ep에 저장한다

for (int j = 0; j \< state.size(); j++) { //state의 사이즈만큼 반복

if (tmp\_ep\_closure[i].compare(state[j]) == 0 && tmp\_ep\_closure[i].compare(next\_state\_ep[j]) != 0) { //만약 tmp\_ep\_closure[i]와 일치하는 state[j]를 발견하였고 next\_state[j]와 tmp\_ep\_closure[i]가 일치하지 않는다면

epsilon\_closure(state, next\_state\_ep, next\_state\_ep[j], tmp\_ep); //그 state[j]의 epsilon에 대한 다음 상태인 next\_state\_ep[j]를 매개 변수로 가지는 epsilon\_closure함수 호출

}

}

}

}

}

위 코드는 매개 변수로 입력받은 상태 s에 epsilon-closure를 적용하는 함수입니다.
우선 상태 s가 여러 개의 상태일 수도 있으니 이를 tokenize하여 tmp\_ep\_closure에 저장합니다.
매개변수로 입력받은 tmp\_ep에 상태 s에 epsilon-closure를 적용한 것을 저장할 것이므로 토큰화한 tmp\_ep\_closure[i]를 tmp\_ep에 이미 저장되어 있는 값들과 비교해 이미 저장되어 있는 값이 있다면 저장하지 않고, 저장되어 있지 않다면 tmp\_ep\_closure[i]를 tmp\_ep에 저장합니다.
저장하였다면, tmp\_ep\_closure[i]와 일치하는 state[j]를 찾아 tmp\_ep\_closure[i]와 next\_state\_ep[j]가 다르다면 next\_state\_ep[j]를 매개변수로 하여 epsilon\_closure 함수를 다시 실행합니다.

//DFA.state에 NFA의 시작 상태를 epsilon\_closure한 것을 DFA의 시작 상태를 집어넣는다.

vector\<string\> tmp\_ep; //epsilon\_closure함수에서 epsilon\_closure 함수의 결과를 저장할 벡터

epsilon\_closure(NFA.state, NFA.next\_state\_ep, NFA.start\_state, tmp\_ep);

DFA.state.push\_back(combine(tmp\_ep, NFA.state));

for (j = 0; j \< DFA.state.size(); j++) { //DFA의 상태의 개수만큼 반복

tmp\_DFA.clear(); //tmp\_DFA 초기화

tmp.assign(DFA.state[j]); //tmp에 DFA.state[j]의 값을 저장한다

tmp\_DFA = tokenize(tmp); //tmp를 tokenize한 것을 tmp\_DFA에 저장한다

if (tmp\_DFA.size() == 1) { //만약 위의 tmp\_DFA에 저장한 다음 상태가 1개의 상태밖에 없다면

for (k = 0; k \< NFA.state.size(); k++) { //NFA의 상태의 개수만큼 반복

if (tmp\_DFA[0].compare(NFA.state[k]) == 0) { //만약 tmp\_DFA에 저장된 값이 NFA.state[k]와 일치한다면

for (a = 0; a \< DFA.input.size(); a++) { //DFA의 입력 심볼의 개수만큼 반복

//NFA.next\_state[k \* DFA.input.size() + a]를 epsilon\_closure한 것을 tmp에 저장한다

tmp\_ep.clear();

epsilon\_closure(NFA.state, NFA.next\_state\_ep, NFA.next\_state[k \* DFA.input.size() + a], tmp\_ep);

tmp.assign(combine(tmp\_ep, NFA.state));

cnt = 0; //cnt를 0으로 만든다

for (l = 0; l \< DFA.state.size(); l++) { //DFA의 state의 개수만큼 반복

if (tmp.compare(DFA.state[l]) != 0) { //만약 tmp와 DFA.state[l]가 일치하지 않는다면

cnt++; //cnt를 1증가시킨다

}

}

if ((cnt == DFA.state.size()) && (tmp != "")) { //만약 cnt가 DFA의 상태의 개수와 일치하고 tmp가 공백이 아니라면

DFA.state.push\_back(tmp); //DFA.state에 tmp를 삽입한다

}

DFA.next\_state.push\_back(tmp); //DFA.next\_state에 tmp를 삽입한다

}

}

}

}

else { //만약 위의 tmp\_DFA에 저장한 다음 상태가 1개의 상태보다 많다면

for (a = 0; a \< DFA.input.size(); a++) { //DFA.input.size()만큼 반복

tmp\_next1.clear(); //tmp\_next1를 초기화

tmp\_next2.clear(); //tmp\_next2를 초기화

//분리되어 tmp\_DFA에 저장된 각각의 상태들의 다음 상태들을 tmp\_next1에 저장한다

for (k = 0; k \< tmp\_DFA.size(); k++) {

for (l = 0; l \< NFA.state.size(); l++) {

if (tmp\_DFA[k].compare(NFA.state[l]) == 0) {

tmp\_next1.push\_back(NFA.next\_state[l \* DFA.input.size() + a]);

}

}

}

for (k = 0; k \< NFA.state.size(); k++) { //순서대로 나열하기 위해 state를 0부터 증가시킨다

cnt = 0; //cnt를 0으로 설정

for (l = 0; l \< tmp\_next1.size(); l++) { //tmp\_next1의 크기만큼 반복

if ((tmp\_next1[l].find(NFA.state[k]) != string::npos) && cnt == 0) { //tmp\_next1[l]에 NFA.state[k]가 존재하고 cnt의 값이 0이라면

tmp\_next2.push\_back(NFA.state[k]); //NFA.state[k] 값을 tmp\_next2에 추가한다

cnt++; //중복을 제거하기 위해 cnt를 1 증가시킨다

}

}

}

tmp.assign(combine(tmp\_next2, NFA.state)); //tmp에 tmp\_next2를 combine한 것을 저장한다

if (tmp\_next2.size() == 0) { //epsilon계산할 다음 상태가 공백이라면

DFA.next\_state.push\_back(""); //DFA.next\_state에 공백을 넣는다

}

else {

//tmp를 epsilon\_closure한 것을 tmp에 저장한다

tmp\_ep.clear();

epsilon\_closure(NFA.state, NFA.next\_state\_ep, tmp, tmp\_ep);

tmp.assign(combine(tmp\_ep, NFA.state));

cnt = 0; //cnt를 0으로 만든다

for (l = 0; l \< DFA.state.size(); l++) { //DFA의 state의 개수만큼 반복

if (tmp.compare(DFA.state[l]) != 0) { //만약 tmp와 DFA.state[k]가 일치하지 않는다면

cnt++; //cnt를 1증가시킨다

}

}

if ((cnt == DFA.state.size()) && (tmp != "")) { //만약 cnt가 DFA의 상태의 개수와 일치하고 tmp가 공백이 아니라면

DFA.state.push\_back(tmp); //DFA.state에 tmp를 삽입한다

}

DFA.next\_state.push\_back(tmp); //DFA.next\_state에 tmp를 삽입한다

}

}

}

}

위의 코드는 입력받은 NFA가 epsilon-NFA일 경우 DFA를 만드는 코드입니다.
우선 NFA의 시작 상태를 epsilon\_closure한 것을 tmp\_ep 벡터에 저장하고, 이를 combine 함수를 통해 합친 것을 DFA.state에 저장합니다. 따라서 DFA.state[0]에 DFA의 시작 상태가 저장됩니다.

DFA의 상태의 개수만큼 j를 증가시키며 반복을 시작합니다.
 DFA.state[j]를 토큰화한 것을 tmp\_DFA에 저장합니다.

만약 tmp\_DFA의 크기가 1이라면 tmp\_DFA[0]와 일치하는 NFA.state[k]를 찾아 NFA.state[k]의 a번째 input에 대한 다음 상태인 NFA.next\_state[k \* DFA.input.size() + a]를 epsilon\_closure한 것을 tmp에 저장합니다.
만약 tmp가 공백이 아니고 DFA.state와 겹치지 않는다면 이를 DFA.state에 삽입합니다.
 DFA.state의 삽입 유무와 상관없이 tmp를 DFA.next\_state에 삽입합니다.

만약 tmp\_DFA의 크기가 1보다 크다면 tmp\_DFA에 저장된 각각의 상태들의 다음 상태들을 tmp\_next1에 저장합니다.
 tmp\_next1에 저장한 값들을 NFA.state에 저장된 순서대로 tmp\_next2에 저장합니다.
 tmp\_next2에 저장된 값들을 tmp에 combine하여 저장하고,
만약 tmp\_next2의 크기가 0이라면 DFA.next\_state에 공백을 저장합니다.
만약 tmp\_next2의 크기가 0이 아니라면 tmp를 epsilon\_closure한 것을 tmp에 저장합니다.
 tmp가 이미 DFA.state에 존재하지 않고, tmp가 공백이 아니라면 DFA.state에 tmp를 삽입합니다.
 tmp의 삽입 여부와 상관없이 tmp를 DFA.next\_state에 삽입합니다.

위 과정을 거치면 DFA의 i번째 상태인 DFA.state[i]의 j번째 입력 심벌인 DFA.input[j]에 대한 다음 상태는 DFA.next\_state[i\*input.size()+j]가 됩니다.

//DFA의 시작 상태 찾기

DFA.start\_state = DFA.state[0];

//DFA의 종결 상태 찾기

for (i = 0; i \< DFA.state.size(); i++) {

for (j = 0; j \< NFA.end\_state.size(); j++) {

if (DFA.state[i].find(NFA.end\_state[j]) != string::npos) {

DFA.end\_state.push\_back(DFA.state[i]);

}

}

}

vector\<int\> equivalence; //각각의 DFA의 상태에 대해 동치류의 번호를 저장할 벡터

vector\<int\> equiv\_num; //동치료의 번호의 개수를 저장할 벡터

//초기에는 종결 상태와 종결 상태가 아닌 2개의 동치류로 나눌 것이므로 equiv\_num에 0,1,2를 삽입한다

equiv\_num.push\_back(0);

equiv\_num.push\_back(1);

equiv\_num.push\_back(2);

for (i = 0; i \< DFA.state.size(); i++) { //모든 DFA의 상태를 검사한다

cnt = 0;

for (j = 0; j \< DFA.end\_state.size(); j++) {

if (DFA.state[i].compare(DFA.end\_state[j]) == 0) { //DFA의 상태가 DFA의 종결 상태에 속한다면

equivalence.push\_back(equiv\_num[2]); //해당하는 DFA의 상태를 동치류 2로 설정한다

cnt++; //cnt를 1 증가시키고

break; //안쪽 반복문을 탈출한다

}

}

if (cnt != 1) { //만약 cnt가 1이 아니라면

equivalence.push\_back(equiv\_num[1]); //DFA의 상태가 DFA의 종결 상태에 속하지 않으므로 동치류 1로 설정한다

}

}

next\_equivalence:

//각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지 저장하기

vector\<int\> equiv\_next; //DFA의 상태가 입력 심벌에 따라 어떤 동치류로 이동되는지 저장할 벡터

for (i = 0; i \< DFA.state.size(); i++) { //DFA의 상태의 개수만큼 반복

for (j = 0; j \< DFA.input.size(); j++) { //DFA의 입력 심벌의 개수만큼 반복

cnt = 0; //cnt를 0으로 설정

for (k = 0; k \< DFA.state.size(); k++) { //DFA의 상태의 개수만큼 반복

if (DFA.next\_state[i \* DFA.input.size() + j].compare(DFA.state[k]) == 0) { //DFA.state[i]의 j번째 입력 심볼에 대한 다음 상태가 DFA.state[k]와 일치한다면

equiv\_next.push\_back(equivalence[k]); //equiv\_next에 state[k]의 동치류인 equivalence[k]를 저장한다

cnt++; //cnt를 1 증가시킨다

}

}

if (cnt == 0) { //DFA.state[i]의 j번째 입력 심볼에 대한 다음 상태가 DFA.state와 일치하는 것이 없다면

equiv\_next.push\_back(0); //equiv\_next에 비어있음을 표시하는 0을 저장한다

}

}

}

for (i = 0; i \< equiv\_next.size(); i += DFA.input.size()) { //i를 0부터 DFA의 입력 심벌의 개수만큼씩 증가시키면 i는 DFA.state[i/input.size()]의 0번째 입력 심벌에 대한 다음 상태의 번호를 가지게 된다

for (j = i + DFA.input.size(); j \< equiv\_next.size(); j += DFA.input.size()) { //j는 i와 동작 원리가 같지만 DFA.state[i/input.size()]의 바로 다음 상태인 DFA.state[(i + DFA.input.size())/input.size()]부터 시작한다

cnt = 0; //cnt를 0으로 설정

for (k = 0; k \< DFA.input.size(); k++) { //DFA의 입력 심벌의 개수만큼 반복

if (equiv\_next[i + k] == equiv\_next[j + k]) { //만약 state[i/input.size()]의 k번째 입력 심벌에 따라 이동되는 동치류와 state[j/input.size()]의 k번째 입력 심벌에 따라 이동되는 동치류가 같다면

cnt++; //cnt를 1 증가시킨다

}

}

if (equivalence[i / DFA.input.size()] == equivalence[j / DFA.input.size()] && cnt != DFA.input.size()) { //만약 동치류는 같지만 입력 심벌에 따라 이동되는 동치류의 번호가 다르다면

if (equiv\_num.size() == 3) { //만약 처음으로 다를 경우(처음으로 다를 경우 아직 equiv\_num에 추가된 번호가 없으므로 equiv\_num의 크기가 처음에 추가했던 3개 그대로일 것이다)

equiv\_num.push\_back(3); //equiv\_num에 3을 넣고

equivalence[j / DFA.input.size()] = equiv\_num[3]; //구별되는 상태의 동치류 번호를 3으로 설정한다

goto next\_equivalence; //새로운 동치류가 생겼으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다

}

else { //처음으로 다른 경우가 아닐 경우

for (k = 3; k \< equiv\_num.size(); k++) { //k는 3부터 equiv\_num에 저장되어 있는 제일 큰 번호까지 반복

for (l = 0; l \< equivalence.size(); l++) { //equivalence의 크기(DFA의 상태의 개수)만큼 반복

if (equivalence[l] == k) { //만약 l번째 state의 동치류가 k와 일치한다면

cnt = 0; //cnt를 0으로 설정

for (a = 0; a \< DFA.input.size(); a++) { //DFA의 입력 심벌의 개수만큼 반복

if (equiv\_next[l \* DFA.input.size() + a] == equiv\_next[j + a]) { //만약 state[l]의 a번째 입력 심벌에 따라 이동되는 동치류가 state[j/input.size()]의 a번째 입력 심벌에 따라 이동되는 동치류와 같다면

cnt++; //cnt를 1 증가시킨다

}

}

if (cnt == DFA.input.size()) { //cnt가 DFA의 입력 심벌의 개수와 같아져 모든 입력 심벌에 따라 이동되는 동치류가 같음이 확인되었다면

equivalence[j / DFA.input.size()] = k; //state[j/input.size()]의 동치류를 k로 설정한다

goto next\_equivalence; //동치류가 바뀌었으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다

}

else { //만약 입력 심벌에 따라 이동되는 동치류가 다르다면

int num = equiv\_num.size(); //equiv\_num.size()는 equiv\_num에 0이 저장되어 있기 때문에 equiv\_num에 저장되어 있는 제일 큰 번호보다 1 클 것이다

equivalence[j / DFA.input.size()] = num; //따라서 equiv\_num에 저장되어 있는 제일 큰 번호보다 1 큰 번호를 state[j/DFA.input.size()]의 동치류의 번호로 설정하고

equiv\_num.push\_back(num); //equiv\_num에 저장되어 있는 제일 큰 번호보다 1 큰 번호를 equiv\_num에 저장한다

goto next\_equivalence; //새로운 동치류가 생겼으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다

}

}

}

}

}

}

}

}

위 코드는 동치 관계를 이용하여 구별되지 않는 상태들을 하나로 합치는 코드입니다.

equivalence 벡터에는 각 DFA의 state의 동치류 번호를 저장할 것이고, equiv\_num 벡터에는 동치류 번호의 종류를 저장할 것이고, equiv\_next 벡터에는 각 DFA의 상태들이 각 입력 심벌에 의해 어떤 동치류로 전이되는지를 저장할 것입니다.

우선 DFA의 state들 중에서 NFA의 종결 상태가 포함된 상태를 찾아 DFA.end\_state에 저장합니다.

우선 종결 상태와 종결 상태가 아닌 동치류로 나눌 것이므로 equiv\_num에는 0,1,2를 순서대로 저장합니다. 0은 다음 상태가 없을 경우 사용할 것입니다. DFA.state[i]가 DFA.end\_state에 포함된다면 equivalence[i]가 2, 포함되지 않는다면 1이 됩니다.

각 DFA의 상태들이 각 입력 심벌에 의해 어떤 동치류로 전이되는지 저장합니다. 만약 전이되는 동치류가 없으면 equiv\_next에 0을 저장합니다. 이 과정을 통하여 DFA.state[i]가 a번째 입력 심벌 DFA.input[a]에 의해 전이되는 동치류는 equiv\_next[i\*DFA.input.size()+a]가 됩니다.

만약 DFA.state[i/DFA.input.size()]와 동치류는 같지만, 입력 심벌에 따라 이동되는 동치류의 번호가 다른 DFA.state[j/DFA.input.size()] 가 발견되었다면, 처음으로 다를 경우, equiv\_num에 3을 추가하고 DFA.state [j / DFA.input.size()]의 동치류를 3으로 설정합니다. 새로운 동치류가 생겼으므로 각 DFA의 상태들이 각 입력 심벌에 의해 어떤 동치류로 전이되는지 저장하는 과정부터 다시 실행합니다.
만약 처음으로 다른 경우가 아닐 경우, 동치류가 3인 것부터 제일 큰 동치류의 각 입력 심벌에 의해 전이되는 동치류와 DFA.state[j/DFA.input.size()]의 각 입력 심벌에 의해 전이되는 동치류를 비교하여 일치하는 것이 발견되었다면
 DFA.state [j / DFA.input.size()]의 동치류를 동일한 동치류와 같은 것으로 설정합니다. 동치류가 변경되었으므로 각 DFA의 상태들이 각 입력 심벌에 의해 어떤 동치류로 전이되는지 저장하는 과정부터 다시 실행합니다.

만약 발견되지 않았다면, equiv\_num에는 0이 저장되어 있으므로 equiv\_num.size()는 equiv\_num에 저장되어 있는 제일 큰 번호보다 1 클 것입니다. 따라서 equiv\_num.size()를 DFA.state [j /
 DFA.input.size()]의 동치류로 설정하고, 이를 equiv\_num에 새로 추가합니다. 새로운 동치류가 생겼으므로 각 DFA의 상태들이 각 입력 심벌에 의해 어떤 동치류로 전이되는지 저장하는 과정부터 다시 실행합니다.

위 과정이 끝나면 동치류 equivalence[i]의 a번째 입력 심벌 DFA.input[a]에 의한 다음 동치류는 equiv\_next[i\*input.size()+a]가 됩니다.

NFA를 입력했을 경우의 결과

![](RackMultipart20230226-1-a6481h_html_bc12482479b6fdc6.png)

![](RackMultipart20230226-1-a6481h_html_59a761017d40111c.png)

epsilon-NFA를 입력했을 경우의 결과

![](RackMultipart20230226-1-a6481h_html_f6f7b454037d1c27.png)

![](RackMultipart20230226-1-a6481h_html_3912481b4f693e50.png)
