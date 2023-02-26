#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(string s);	//문자열 s를 띄어쓰기를 기준으로 토큰화하여 반환하는 함수
string combine(vector<string> a, vector<string> state);	//vector a에 담긴 문자열들을 하나로 합쳐 반환하는 함수
void epsilon_closure(vector<string> state, vector<string> next_state_ep, string s, vector<string>& tmp_ep);	//epsilon_closure 함수
void print_state_table(vector<string> state, vector<string> next_state, vector<string> input, string state_transition_function);	//상태 전이표를 출력하는 함수
void print_state_table_equiv(vector<int> state, vector<int> next_state, vector<string> input, string state_transition_function);	//구별되지 않는 상태들을 하나로 합친 후 최소화한 DFA를 출력하는 함수

struct FA {
	vector<string> state;	//FA의 상태들이 저장될 벡터
	vector<string> input;	//FA의 입력 심벌들이 저장될 벡터
	string epsilon_exsist;	//epsilon-NFA인지 아닌지를 구분할 문자열

	string state_transition_function = "δ";	//상태 전이 함수
	vector<string> next_state;	//상태들의 입력 심볼들에 대한 다음 상태 입력
	vector<string> next_state_ep;	//epsilon-NFA일 경우 입력 심볼이 epsilon일 때의 다음 상태 입력

	string start_state;	//FA의 시작 상태
	vector<string> end_state;	//FA의 종결 상태

};

int main() {
	cout << "만약 여러 개의 입력을 해야 할 경우, 항상 오름차순으로 적어주시고 각 입력들은 띄어쓰기로 구분해주세요." << endl;
	cout << "어떤 상태의 입력 심볼에 대한 다음 상태가 없을 경우 아무것도 입력하지 않고 엔터를 눌러주세요." << endl;
	cout << "입력 예시: 상태 1의 입력 심볼 a에 대한 다음상태:1 2 3" << endl << endl;

	FA NFA;	//비결정적 유한 오토마타 생성

epsilon_exsist:
	cout << endl << "만약 입력하실 NFA가 epsilon-NFA라면 y, 아니라면 n를 입력해주세요.";
	getline(cin, NFA.epsilon_exsist); 	//epsilon-NFA인지 아닌지 구분

	if (NFA.epsilon_exsist.compare("y") != 0&& NFA.epsilon_exsist.compare("n") != 0) {
		cout << "올바른 입력이 아닙니다. 다시 입력해주세요." << endl;
		NFA.epsilon_exsist.clear();

		goto epsilon_exsist;
	}

	//상태 입력
	string state_in;	//상태를 입력받는 변수

	cout << endl << "NFA의 상태들을 순서대로 입력해주세요. 각 상태들은 띄어쓰기로 구분해주세요.";
	getline(cin, state_in);

	NFA.state = tokenize(state_in);	//입력받은 상태를 띄어쓰기를 기준으로 토큰화하여 NFA.state에 저장한다

	//입력 심볼 입력
	if (NFA.epsilon_exsist.compare("y") == 0) {
		cout << endl << "epsilon을 제외한 NFA의 입력 심벌들을 순서대로 입력해주세요.";
	}
	else if (NFA.epsilon_exsist.compare("n") == 0) {
		cout << endl << "NFA의 입력 심벌들을 순서대로 입력해주세요.";
	}

	string input_in;	//입력 심벌을 입력받는 변수 
	getline(cin, input_in);

	NFA.input = tokenize(input_in);	//입력받은 입력 심벌을 띄어쓰기를 기준으로 토큰화하여 NFA.input에 저장한다

	//상태들의 입력 심볼들에 대한 다음 상태 입력
	string nextstate_in;	//다음 상태를 입력받는 변수
	cout << endl;

	int i, j, k, l, a;	//반복문에서 사용할 변수들

	for (i = 0; i < NFA.state.size(); i++) {
		for (j = 0; j < NFA.input.size(); j++) {
			cout << NFA.state[i] << "의 입력 심볼 " << NFA.input[j] << "에 대한 다음 상태를 입력해주세요: ";
			getline(cin, nextstate_in);

			NFA.next_state.push_back(nextstate_in);	//입력받은 다음 상태를 NFA.nex_state에 저장한다
		}
		cout << endl;
	}

	//epsilon-NFA일 경우 입력 심볼이 epsilon일 때의 다음 상태 입력
	if (NFA.epsilon_exsist.compare("y") == 0) {
		string nextstate_in_ep;	//epsilon에 대한 다음 상태를 입력받을 변수
		cout << "입력 심볼 epsilon에 대한 다음 상태를 입력할 때, 자기 자신은 입력해도 되고 안해도 됩니다." << endl << endl;

		for (i = 0; i < NFA.state.size(); i++) {

			cout << NFA.state[i] << "의 입력 심볼 epsilon에 대한 다음 상태를 입력해주세요: ";
			getline(cin, nextstate_in_ep);
			NFA.next_state_ep.push_back(nextstate_in_ep);	//입력받은 epsilon에 대한 다음 상태를 NFA.nex_state_ep에 저장한다
		}
	}

	//시작 상태 입력
	while (true) {
		cout << endl << "시작 상태를 입력해주세요: ";
		getline(cin, NFA.start_state);

		for (i = 0; i < NFA.state.size(); i++) {
			if (NFA.start_state.compare(NFA.state[i]) == 0) {	//입력받은 시작 상태가 존재할 경우
				goto end_state_input;	//바깥의 while문을 탈출한다
			}
		}
		cout << "입력하신 상태가 존재하지 않습니다." << endl << "다시 입력해주세요." << endl;
	}

	//종결 상태 입력
end_state_input:
	string end_state_in;	//종결 상태를 입력받을 변수

	cout << endl << "종결 상태를 입력해주세요. 만약 여러개의 상태가 존재할 경우 띄어쓰기로 구분해주세요.";
	getline(cin, end_state_in);

	NFA.end_state = tokenize(end_state_in);	//입력받은 종결 상태를 띄어쓰기를 기준으로 토큰화하여 NFA.end_state에 저장한다

	//도달 불가능한 상태들을 제외한 DFA 생성 시작
	FA DFA;	//결정적 유한 오토마타 생성

	DFA.input = NFA.input;	//DFA의 input을 NFA의 input과 같게 설정한다

	string tmp;	//문자열을 tokenize할 일이 있을 때, 원본 문자열을 자르면 안 되므로 임시로 문자열을 복사하여 저장해두거나 토큰화된 문자열을 다시 하나로 합칠 때 사용할 변수
	int cnt = 0;	//DFA를 생성할 때 무언가의 개수를 셀 일이 있으면 사용할 변수

	vector<string> tmp_DFA;	//DFA에 여러 개의 상태가 존재한다면 이 상태들을 임시로 분리하여 담아둘 벡터
	vector<string> tmp_next1;	//tmp_DFA의 분리된 벡터들의 다음 상태들을 임시로 담아둘 벡터
	vector<string> tmp_next2;	//NFA를 DFA로 바꿀 때 여러가지 용도로 값들을 입시로 저장할 때 사용할 벡터

	//입력받은 NFA가 epsilon-NFA가 아니라면
	if (NFA.epsilon_exsist.compare("n") == 0) {

		//DFA의 시작 상태를 DFA.state에 저장하고 시작 상태의 다음 상태를 DFA.next_state와 중복이 되지 않는다면 DFA.state에 저장
		for (i = 0; i < NFA.state.size(); i++) {	//NFA의 상태의 개수만큼 반복
			if (NFA.start_state.compare(NFA.state[i]) == 0) {	//NFA의 시작 상태가 NFA.state[i]라면
				DFA.state.push_back(NFA.state[i]);	//DFA의 첫 번째 상태로 NFA.state[i]를 집어넣는다

				for (j = 0; j < DFA.input.size(); j++) {	//DFA의 input의 개수만큼 반복
					cnt = 0;	//cnt를 0으로 설정

					for (k = 0; k < DFA.state.size(); k++) {	//DFA의 상태의 개수만큼 반복
						if (NFA.next_state[i * DFA.input.size() + j].compare(DFA.state[k]) != 0) {	//NFA의 시작 상태의 다음 상태들이 DFA의 상태들과 겹치지 않는다면
							cnt++;	//cnt를 1 증가시킨다
						}
					}

					if (cnt == DFA.state.size()) {	//cnt가 DFA의 상태의 개수와 같아져 중복이 없음이 확인되었다면
						DFA.state.push_back(NFA.next_state[i * DFA.input.size() + j]);	//DFA_state에 NFA의 시작 상태의 다음 상태들을 추가한다
					}
					DFA.next_state.push_back(NFA.next_state[i * DFA.input.size() + j]);	//DFA의 시작 상태의 다음 상태들에 NFA의 시작 상태의 다음 상태들을 추가한다
				}

				break;
			}
		}

		//DFA의 시작 상태를 제외한 다른 DFA.state들의 각 입력 심벌에 따른 다음 상태를 DFA.next_state와 중복이 되지 않는다면 DFA.state에 저장
		for (i = 1; i < DFA.state.size(); i++) {	//DFA의 시작 상태의 다음 상태들은 이미 DFA.next_state에 저장해 두었으므로 i=0인 시작 상태를 제외하고 i=1부터 시작
			tmp_DFA.clear();	//tmp_DFA 벡터를 초기화한다
			tmp.assign(DFA.state[i]);	//tmp에 DFA_state[i]를 임시로 저장해둔다
			tmp_DFA = tokenize(tmp);	//tmp_DFA에 tmp를 tokenize한 것을 저장해둔다

			if (tmp_DFA.size() == 1) {	//만약 DFA.state[i]가 한 개의 상태라면
				for (j = 0; j < NFA.state.size(); j++) {	//NFA의 상태의 개수만큼 반복
					if (tmp_DFA[0].compare(NFA.state[j]) == 0) {	//tmp_DFA와 같은 상태를 state에서 찾아
						cnt = 0;	//cnt를 0으로 설정

						for (k = 0; k < DFA.input.size(); k++) {	//DFA의 입력 심볼의 개수만큼 반복
							DFA.next_state.push_back(NFA.next_state[j * DFA.input.size() + k]);	//DFA.next_state에 현재 NFA.state[j]의 next state를 추가한다

							for (l = 0; l < DFA.state.size(); l++) {	//모든 DFA.state[]를 비교하기 위하여 DFA.state.size()만큼 반복
								if (DFA.state[l].compare(NFA.next_state[j * DFA.input.size() + k]) != 0) {	//위에서 DFA.next_state에 추가된 것들이 DFA_state[l]과 중복되지 않는다면
									cnt++;	//cnt를 1 증가시킨다
								}
							}

							if (cnt == DFA.state.size()) {	//만약 cnt가 DFA_state.size()와 같아져 중복이 없음이 확인되었다면
								DFA.state.push_back(NFA.next_state[j * DFA.input.size() + k]);	//DFA_state에 위에서 DFA.next_state에 추가된 것들을 추가한다
							}
						}
					}
				}
			}

			else {	//만약 DFA.state[i]가 여러 개의 상태라면
				for (a = 0; a < DFA.input.size(); a++) {	//DFA의 입력 심벌의 개수만큼 반복
					tmp_next1.clear();	//tmp_next1 벡터를 초기화한다
					tmp_next2.clear();	//tmp_next2 벡터를 초기화한다

					//분리된 DFA의 다음 상태 저장하기
					for (j = 0; j < tmp_DFA.size(); j++) {	//DFA.state[i]에 저장되어 있는 상태의 개수만큼 반복
						for (k = 0; k < NFA.state.size(); k++) {	//NFA의 상태의 개수만큼 반복
							if (tmp_DFA[j].compare(NFA.state[k]) == 0) {	//state[i]의 분리된 상태가 NFA.state[k]와 일치한다면
								tmp_next1.push_back(NFA.next_state[k * DFA.input.size() + a]);	//NFA.state[k]의 a번째 입력 심볼에 대한 다음 상태를 tmp_next1에 저장
							}
						}
					}

					for (j = 0; j < NFA.state.size(); j++) {	//순서대로 나열하기 위해 NFA.state의 j를 0부터 증가시킨다
						cnt = 0;	//중복 제거를 위한 cnt

						for (k = 0; k < tmp_next1.size(); k++) {	//tmp_next1의 크기만큼 반복
							if ((tmp_next1[k].find(NFA.state[j]) != string::npos) && cnt == 0) {	//tmp_next1[k]에 NFA.state[j]가 존재하고 cnt의 값이 0이라면
								tmp_next2.push_back(NFA.state[j]);	//NFA.state[j] 값을 tmp_next2에 추가한다
								cnt++;	//중복된 값을 tmp_next2에 추가하지 않기 위하여 cnt를 1 증가시킨다
							}
						}
					}

					//tmp_next2에 저장된 값들을 tmp에 합쳐 저장한다
					tmp.assign(combine(tmp_next2, NFA.state));

					//tmp의 값이 DFA의 상태들과 중복되지 않는다면
					cnt = 0;
					for (j = 0; j < DFA.state.size(); j++) {	//tmp의 값이 DFA의 상태들과 중복되는지 검사
						if (tmp.compare(DFA.state[j]) != 0) {
							cnt++;
						}
					}
					if (cnt == DFA.state.size()) {	//tmp의 값이 DFA의 상태들과 중복되지 않는다면
						DFA.state.push_back(tmp);	//DFA.state에 tmp 삽입
					}

					DFA.next_state.push_back(tmp);	//DFA.next_state에 tmp 삽입
				}
			}
		}

	}	//NFA일 경우 끝

	else if (NFA.epsilon_exsist.compare("y") == 0) {	//epsilon-NFA라면

		//DFA.state에 NFA의 시작 상태를 epsilon_closure한 것을 DFA의 시작 상태를 집어넣는다.
		vector<string> tmp_ep;	//epsilon_closure함수에서 epsilon_closure 함수의 결과를 저장할 벡터
		epsilon_closure(NFA.state, NFA.next_state_ep, NFA.start_state, tmp_ep);
		DFA.state.push_back(combine(tmp_ep, NFA.state));
		
		for (j = 0; j < DFA.state.size(); j++) {	//DFA의 상태의 개수만큼 반복
			tmp_DFA.clear();	//tmp_DFA 초기화
			tmp.assign(DFA.state[j]);	//tmp에 DFA.state[j]의 값을 저장한다
			tmp_DFA = tokenize(tmp);	//tmp를 tokenize한 것을 tmp_DFA에 저장한다

			if (tmp_DFA.size() == 1) {	//만약 위의 tmp_DFA에 저장한 다음 상태가 1개의 상태밖에 없다면
				for (k = 0; k < NFA.state.size(); k++) {	//NFA의 상태의 개수만큼 반복
					if (tmp_DFA[0].compare(NFA.state[k]) == 0) {	//만약 tmp_DFA에 저장된 값이 NFA.state[k]와 일치한다면
						for (a = 0; a < DFA.input.size(); a++) {	//DFA의 입력 심볼의 개수만큼 반복
							//NFA.next_state[k * DFA.input.size() + a]를 epsilon_closure한 것을 tmp에 저장한다
							tmp_ep.clear();
							epsilon_closure(NFA.state, NFA.next_state_ep, NFA.next_state[k * DFA.input.size() + a], tmp_ep);
							tmp.assign(combine(tmp_ep, NFA.state));
							
							cnt = 0;	//cnt를 0으로 만든다
							for (l = 0; l < DFA.state.size(); l++) {	//DFA의 state의 개수만큼 반복
								if (tmp.compare(DFA.state[l]) != 0) {	//만약 tmp와 DFA.state[l]가 일치하지 않는다면
									cnt++;	//cnt를 1증가시킨다
								}
							}
							if ((cnt == DFA.state.size()) && (tmp != "")) {	//만약 cnt가 DFA의 상태의 개수와 일치하고 tmp가 공백이 아니라면
								DFA.state.push_back(tmp);	//DFA.state에 tmp를 삽입한다
							}
							DFA.next_state.push_back(tmp);	//DFA.next_state에 tmp를 삽입한다
						}
					}
				}
			}

			else {	//만약 위의 tmp_DFA에 저장한 다음 상태가 1개의 상태보다 많다면
				for (a = 0; a < DFA.input.size(); a++) {	//DFA.input.size()만큼 반복
					tmp_next1.clear();	//tmp_next1를 초기화
					tmp_next2.clear();	//tmp_next2를 초기화

					//분리되어 tmp_DFA에 저장된 각각의 상태들의 다음 상태들을 tmp_next1에 저장한다
					for (k = 0; k < tmp_DFA.size(); k++) {
						for (l = 0; l < NFA.state.size(); l++) {
							if (tmp_DFA[k].compare(NFA.state[l]) == 0) {
								tmp_next1.push_back(NFA.next_state[l * DFA.input.size() + a]);
							}
						}
					}

					for (k = 0; k < NFA.state.size(); k++) {	//순서대로 나열하기 위해 state를 0부터 증가시킨다
						cnt = 0;	//cnt를 0으로 설정

						for (l = 0; l < tmp_next1.size(); l++) {	//tmp_next1의 크기만큼 반복
							if ((tmp_next1[l].find(NFA.state[k]) != string::npos) && cnt == 0) {	//tmp_next1[l]에 NFA.state[k]가 존재하고 cnt의 값이 0이라면
								tmp_next2.push_back(NFA.state[k]);	//NFA.state[k] 값을 tmp_next2에 추가한다
								cnt++;	//중복을 제거하기 위해 cnt를 1 증가시킨다
							}
						}
					}

					tmp.assign(combine(tmp_next2, NFA.state));	//tmp에 tmp_next2를 combine한 것을 저장한다
					if (tmp_next2.size() == 0) {	//epsilon계산할 다음 상태가 공백이라면
						DFA.next_state.push_back("");	//DFA.next_state에 공백을 넣는다
					}

					else {
						//tmp를 epsilon_closure한 것을 tmp에 저장한다
						tmp_ep.clear();
						epsilon_closure(NFA.state, NFA.next_state_ep, tmp, tmp_ep);
						tmp.assign(combine(tmp_ep, NFA.state));

						cnt = 0;	//cnt를 0으로 만든다
						for (l = 0; l < DFA.state.size(); l++) {	//DFA의 state의 개수만큼 반복
							if (tmp.compare(DFA.state[l]) != 0) {	//만약 tmp와 DFA.state[k]가 일치하지 않는다면
								cnt++;	//cnt를 1증가시킨다
							}
						}
						if ((cnt == DFA.state.size()) && (tmp != "")) {	//만약 cnt가 DFA의 상태의 개수와 일치하고 tmp가 공백이 아니라면
							DFA.state.push_back(tmp);	//DFA.state에 tmp를 삽입한다
						}

						DFA.next_state.push_back(tmp);	//DFA.next_state에 tmp를 삽입한다

					}
				}
			}
		}

	}	//epsilon-NFA일 경우 끝

	cout << endl << "도달 불가능한 상태들을 제거한 DFA" << endl << endl;
	print_state_table(DFA.state, DFA.next_state, DFA.input, DFA.state_transition_function);
	cout << endl;

	//구별되지 않는 상태들을 하나로 합치기
	if (DFA.state.size() > 1) {	//DFA.state가 2개 이상일 경우 줄일 수 있는 것이 있는지 검사한다

		//DFA의 시작 상태 찾기
		DFA.start_state = DFA.state[0];

		//DFA의 종결 상태 찾기
		for (i = 0; i < DFA.state.size(); i++) {
			for (j = 0; j < NFA.end_state.size(); j++) {
				if (DFA.state[i].find(NFA.end_state[j]) != string::npos) {
					DFA.end_state.push_back(DFA.state[i]);
				}
			}
		}

		vector<int> equivalence;	//각각의 DFA의 상태에 대해 동치류의 번호를 저장할 벡터
		vector<int> equiv_num;	//동치료의 번호의 개수를 저장할 벡터

		//초기에는 종결 상태와 종결 상태가 아닌 2개의 동치류로 나눌 것이므로 equiv_num에 0,1,2를 삽입한다
		equiv_num.push_back(0);
		equiv_num.push_back(1);
		equiv_num.push_back(2);
		for (i = 0; i < DFA.state.size(); i++) {	//모든 DFA의 상태를 검사한다
			cnt = 0;

			for (j = 0; j < DFA.end_state.size(); j++) {
				if (DFA.state[i].compare(DFA.end_state[j]) == 0) {	//DFA의 상태가 DFA의 종결 상태에 속한다면
					equivalence.push_back(equiv_num[2]);	//해당하는 DFA의 상태를 동치류 2로 설정한다
					cnt++;	//cnt를 1 증가시키고
					break;	//안쪽 반복문을 탈출한다
				}
			}

			if (cnt != 1) {	//만약 cnt가 1이 아니라면
				equivalence.push_back(equiv_num[1]);	//DFA의 상태가 DFA의 종결 상태에 속하지 않으므로 동치류 1로 설정한다
			}
		}

	next_equivalence:
		//각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지 저장하기
		vector<int> equiv_next;	//DFA의 상태가 입력 심벌에 따라 어떤 동치류로 이동되는지 저장할 벡터

		for (i = 0; i < DFA.state.size(); i++) {	//DFA의 상태의 개수만큼 반복
			for (j = 0; j < DFA.input.size(); j++) {	//DFA의 입력 심벌의 개수만큼 반복
				cnt = 0;	//cnt를 0으로 설정

				for (k = 0; k < DFA.state.size(); k++) {	//DFA의 상태의 개수만큼 반복
					if (DFA.next_state[i * DFA.input.size() + j].compare(DFA.state[k]) == 0) {	//DFA.state[i]의 j번째 입력 심볼에 대한 다음 상태가 DFA.state[k]와 일치한다면
						equiv_next.push_back(equivalence[k]);	//equiv_next에 state[k]의 동치류인 equivalence[k]를 저장한다
						cnt++;	//cnt를 1 증가시킨다
					}
				}
				if (cnt == 0) {	//DFA.state[i]의 j번째 입력 심볼에 대한 다음 상태가 DFA.state와 일치하는 것이 없다면
					equiv_next.push_back(0);	//equiv_next에 비어있음을 표시하는 0을 저장한다
				}
			}
		}

		for (i = 0; i < equiv_next.size(); i += DFA.input.size()) {	//i를 0부터 DFA의 입력 심벌의 개수만큼씩 증가시키면 i는 DFA.state[i/input.size()]의 0번째 입력 심벌에 대한 다음 상태의 번호를 가지게 된다
			for (j = i + DFA.input.size(); j < equiv_next.size(); j += DFA.input.size()) {	//j는 i와 동작 원리가 같지만 DFA.state[i/input.size()]의 바로 다음 상태인 DFA.state[(i + DFA.input.size())/input.size()]부터 시작한다
				cnt = 0;	//cnt를 0으로 설정

				for (k = 0; k < DFA.input.size(); k++) {	//DFA의 입력 심벌의 개수만큼 반복
					if (equiv_next[i + k] == equiv_next[j + k]) {	//만약 state[i/input.size()]의 k번째 입력 심벌에 따라 이동되는 동치류와 state[j/input.size()]의 k번째 입력 심벌에 따라 이동되는 동치류가 같다면
						cnt++;	//cnt를 1 증가시킨다
					}
				}

				if (equivalence[i / DFA.input.size()] == equivalence[j / DFA.input.size()] && cnt != DFA.input.size()) {	//만약 동치류는 같지만 입력 심벌에 따라 이동되는 동치류의 번호가 다르다면
					if (equiv_num.size() == 3) {	//만약 처음으로 다를 경우(처음으로 다를 경우 아직 equiv_num에 추가된 번호가 없으므로 equiv_num의 크기가 처음에 추가했던 3개 그대로일 것이다)
						equiv_num.push_back(3);	//equiv_num에 3을 넣고
						equivalence[j / DFA.input.size()] = equiv_num[3];	//구별되는 상태의 동치류 번호를 3으로 설정한다

						goto next_equivalence;	//새로운 동치류가 생겼으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다
					}

					else {	//처음으로 다른 경우가 아닐 경우
						for (k = 3; k < equiv_num.size(); k++) {	//k는 3부터 equiv_num에 저장되어 있는 제일 큰 번호까지 반복
							for (l = 0; l < equivalence.size(); l++) {	//equivalence의 크기(DFA의 상태의 개수)만큼 반복
								if (equivalence[l] == k) {	//만약 l번째 state의 동치류가 k와 일치한다면
									cnt = 0;	//cnt를 0으로 설정

									for (a = 0; a < DFA.input.size(); a++) {	//DFA의 입력 심벌의 개수만큼 반복
										if (equiv_next[l * DFA.input.size() + a] == equiv_next[j + a]) {	//만약 state[l]의 a번째 입력 심벌에 따라 이동되는 동치류가 state[j/input.size()]의 a번째 입력 심벌에 따라 이동되는 동치류와 같다면
											cnt++;	//cnt를 1 증가시킨다
										}
									}

									if (cnt == DFA.input.size()) {	//cnt가 DFA의 입력 심벌의 개수와 같아져 모든 입력 심벌에 따라 이동되는 동치류가 같음이 확인되었다면
										equivalence[j / DFA.input.size()] = k;	//state[j/input.size()]의 동치류를 k로 설정한다

										goto next_equivalence;	//동치류가 바뀌었으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다
									}

									else {	//만약 입력 심벌에 따라 이동되는 동치류가 다르다면
										int num = equiv_num.size();	//equiv_num.size()는 equiv_num에 0이 저장되어 있기 때문에 equiv_num에 저장되어 있는 제일 큰 번호보다 1 클 것이다
										equivalence[j / DFA.input.size()] = num;	//따라서 equiv_num에 저장되어 있는 제일 큰 번호보다 1 큰 번호를 state[j/DFA.input.size()]의 동치류의 번호로 설정하고
										equiv_num.push_back(num);	//equiv_num에 저장되어 있는 제일 큰 번호보다 1 큰 번호를 equiv_num에 저장한다

										goto next_equivalence;	//새로운 동치류가 생겼으므로 각 DFA들이 입력 심벌에 따라 어떤 동치류로 이동되는지를 다시 설정해야 한다
									}
								}
							}
						}
					}
				}
			}
		}

		cout << "각 DFA의 상태들의 동치류의 번호" << endl;
		for (i = 0; i < DFA.state.size(); i++) {
			cout << "[" << DFA.state[i] << "]: " << equivalence[i] << endl;
		}

		//시작 상태 출력
		cout << endl << "시작 상태: " << equivalence[0] << endl;

		//종결 상태 출력
		vector<int> tmp_equiv;	//이미 출력한 종결 상태를 또 출력하지 않기 위해 이미 출력한 종결 상태를 저장해놓을 벡터
		tmp_equiv.push_back(0);

		cout << "종결 상태: ";
		for (i = 0; i < DFA.state.size(); i++) {
			for (j = 0; j < DFA.end_state.size(); j++) {
				if (DFA.end_state[j].compare(DFA.state[i]) == 0) {	//만약 DFA.end_state[j]와 DFA.state[i]가 일치한다면
					cnt = 0;	//cnt를 0으로 설정

					for (k = 0; k < tmp_equiv.size(); k++) {
						if (equivalence[i] == tmp_equiv[k]) {	//tmp_equiv에 이미 찾은 종결 상태 equivalence[i]가 있다면
							cnt++;	//cnt를 1 증가시킨다
						}
					}

					if (cnt == 0) {	//cnt가 0이어서 중복이 되지 않는다면
						cout << equivalence[i] << " ";	//찾은 종결 상태인 equivalence[i]를 출력
						tmp_equiv.push_back(equivalence[i]);	//이미 출력한 것을 또다시 출력하지 않기 위해 equivalence[i]를 tmp_equiv에 저장한다
					}
				}
			}
		}
		cout << endl << endl;

		print_state_table_equiv(equivalence, equiv_next, DFA.input, DFA.state_transition_function);

	}	//reduced 끝

	return 0;
}

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

string combine(vector<string> a, vector<string> state) {	//vector a에 담긴 문자열들을 하나로 합쳐 반환하는 함수
	string s;
	int cnt = 0;
	
	//벡터 a에 저장되어 있는 값들을 string s에 합칠 때, 순서대로 합치기 위해서 이중 for문을 사용한다.
	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (a[j].find(state[i]) != string::npos) {
				if (cnt == 0) {	//s에 제일 처음으로 저장할 경우
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

void epsilon_closure(vector<string> state, vector<string> next_state_ep, string s, vector<string>& tmp_ep) {	//epsilon_closure 함수
	vector<string> tmp_ep_closure;	//s를 토큰화하여 저장할 변수

	tmp_ep_closure = tokenize(s);	//s를 토큰화하여 tmp_ep_closure에 저장한다

	for (int i = 0; i < tmp_ep_closure.size(); i++) {	//tmp_ep_closure에 담긴 상태의 개수만큼 반복
		int cnt = 0;	//cnt를 0으로 설정

		for (int a = 0; a < tmp_ep.size(); a++) {	//tmp_ep의 크기만큼 반복
			if (tmp_ep_closure[i].compare(tmp_ep[a]) == 0) {	//만약 tmp_ep_closure[i]와 tmp_ep[a]가 같으면
				cnt++;	//cnt를 1 증가시킨다
			}
		}

		if (cnt == 0) {	//tmp_ep_closure[i]와 tmp_ep[a]가 같음이 발견되지 않아 cnt가 증가되지 않았다면 중복이 없다는 뜻이므로
			tmp_ep.push_back(tmp_ep_closure[i]);	//tmp_ep_closure[i]를 tmp_ep에 저장한다

			for (int j = 0; j < state.size(); j++) {	//state의 사이즈만큼 반복
				if (tmp_ep_closure[i].compare(state[j]) == 0 && tmp_ep_closure[i].compare(next_state_ep[j]) != 0) {	//만약 tmp_ep_closure[i]와 일치하는 state[j]를 발견하였고 next_state[j]와 tmp_ep_closure[i]가 일치하지 않는다면
					epsilon_closure(state, next_state_ep, next_state_ep[j], tmp_ep);	//그 state[j]의 epsilon에 대한 다음 상태인 next_state_ep[j]를 매개 변수로 가지는 epsilon_closure함수 호출
				}
			}
		}
	}
}

void print_state_table(vector<string> state, vector<string> next_state, vector<string> input, string state_transition_function) {	//상태 전이표를 출력하는 함수
	//입력 심볼 출력
	cout << "  " << state_transition_function << "  ";
	for (int i = 0; i < input.size(); i++) {
		cout << "|   " << input[i] << "   ";
	}
	cout << endl;

	//상태들 출력
	for (int i = 0; i < state.size(); i++) {
		cout << " [" << state[i] << "] ";
		for (int j = 0; j < input.size(); j++) {
			cout << "| [";
			if (next_state[i * input.size() + j].compare("") == 0) {
				cout << "Φ";
			}
			else {
				cout << next_state[i * input.size() + j];
			}
			cout << "] ";
		}
		cout << endl;
	}
}

void print_state_table_equiv(vector<int> state, vector<int> next_state, vector<string> input, string state_transition_function) {	//구별되지 않는 상태들을 하나로 합친 후 최소화한 DFA를 출력하는 함수
	//입력 심볼 출력
	cout << "  " << state_transition_function << " ";
	for (int i = 0; i < input.size(); i++) {
		cout << "|   " << input[i] << "  ";
	}
	cout << endl;

	vector<int> tmp_int;
	tmp_int.push_back(0);

	//상태들 출력
	for (int i = 0; i < state.size(); i++) {
		int cnt = 0;

		for (int j = 0; j < tmp_int.size(); j++) {
			if (state[i] == tmp_int[j]) {
				cnt++;
			}
		}
		if (cnt == 0) {
			cout << " [" << state[i] << "] ";
			tmp_int.push_back(state[i]);

			for (int j = 0; j < input.size(); j++) {
				if (next_state[i * input.size() + j] == 0) {
					cout << "| [";
					cout << "Φ";
				}
				else {
					cout << "|  [";
					cout << next_state[i * input.size() + j];
				}
				cout << "] ";
			}
			cout << endl;
		}
	}
}