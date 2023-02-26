#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenize(string s);	//���ڿ� s�� ���⸦ �������� ��ūȭ�Ͽ� ��ȯ�ϴ� �Լ�
string combine(vector<string> a, vector<string> state);	//vector a�� ��� ���ڿ����� �ϳ��� ���� ��ȯ�ϴ� �Լ�
void epsilon_closure(vector<string> state, vector<string> next_state_ep, string s, vector<string>& tmp_ep);	//epsilon_closure �Լ�
void print_state_table(vector<string> state, vector<string> next_state, vector<string> input, string state_transition_function);	//���� ����ǥ�� ����ϴ� �Լ�
void print_state_table_equiv(vector<int> state, vector<int> next_state, vector<string> input, string state_transition_function);	//�������� �ʴ� ���µ��� �ϳ��� ��ģ �� �ּ�ȭ�� DFA�� ����ϴ� �Լ�

struct FA {
	vector<string> state;	//FA�� ���µ��� ����� ����
	vector<string> input;	//FA�� �Է� �ɹ����� ����� ����
	string epsilon_exsist;	//epsilon-NFA���� �ƴ����� ������ ���ڿ�

	string state_transition_function = "��";	//���� ���� �Լ�
	vector<string> next_state;	//���µ��� �Է� �ɺ��鿡 ���� ���� ���� �Է�
	vector<string> next_state_ep;	//epsilon-NFA�� ��� �Է� �ɺ��� epsilon�� ���� ���� ���� �Է�

	string start_state;	//FA�� ���� ����
	vector<string> end_state;	//FA�� ���� ����

};

int main() {
	cout << "���� ���� ���� �Է��� �ؾ� �� ���, �׻� ������������ �����ֽð� �� �Էµ��� ����� �������ּ���." << endl;
	cout << "� ������ �Է� �ɺ��� ���� ���� ���°� ���� ��� �ƹ��͵� �Է����� �ʰ� ���͸� �����ּ���." << endl;
	cout << "�Է� ����: ���� 1�� �Է� �ɺ� a�� ���� ��������:1 2 3" << endl << endl;

	FA NFA;	//������� ���� ���丶Ÿ ����

epsilon_exsist:
	cout << endl << "���� �Է��Ͻ� NFA�� epsilon-NFA��� y, �ƴ϶�� n�� �Է����ּ���.";
	getline(cin, NFA.epsilon_exsist); 	//epsilon-NFA���� �ƴ��� ����

	if (NFA.epsilon_exsist.compare("y") != 0&& NFA.epsilon_exsist.compare("n") != 0) {
		cout << "�ùٸ� �Է��� �ƴմϴ�. �ٽ� �Է����ּ���." << endl;
		NFA.epsilon_exsist.clear();

		goto epsilon_exsist;
	}

	//���� �Է�
	string state_in;	//���¸� �Է¹޴� ����

	cout << endl << "NFA�� ���µ��� ������� �Է����ּ���. �� ���µ��� ����� �������ּ���.";
	getline(cin, state_in);

	NFA.state = tokenize(state_in);	//�Է¹��� ���¸� ���⸦ �������� ��ūȭ�Ͽ� NFA.state�� �����Ѵ�

	//�Է� �ɺ� �Է�
	if (NFA.epsilon_exsist.compare("y") == 0) {
		cout << endl << "epsilon�� ������ NFA�� �Է� �ɹ����� ������� �Է����ּ���.";
	}
	else if (NFA.epsilon_exsist.compare("n") == 0) {
		cout << endl << "NFA�� �Է� �ɹ����� ������� �Է����ּ���.";
	}

	string input_in;	//�Է� �ɹ��� �Է¹޴� ���� 
	getline(cin, input_in);

	NFA.input = tokenize(input_in);	//�Է¹��� �Է� �ɹ��� ���⸦ �������� ��ūȭ�Ͽ� NFA.input�� �����Ѵ�

	//���µ��� �Է� �ɺ��鿡 ���� ���� ���� �Է�
	string nextstate_in;	//���� ���¸� �Է¹޴� ����
	cout << endl;

	int i, j, k, l, a;	//�ݺ������� ����� ������

	for (i = 0; i < NFA.state.size(); i++) {
		for (j = 0; j < NFA.input.size(); j++) {
			cout << NFA.state[i] << "�� �Է� �ɺ� " << NFA.input[j] << "�� ���� ���� ���¸� �Է����ּ���: ";
			getline(cin, nextstate_in);

			NFA.next_state.push_back(nextstate_in);	//�Է¹��� ���� ���¸� NFA.nex_state�� �����Ѵ�
		}
		cout << endl;
	}

	//epsilon-NFA�� ��� �Է� �ɺ��� epsilon�� ���� ���� ���� �Է�
	if (NFA.epsilon_exsist.compare("y") == 0) {
		string nextstate_in_ep;	//epsilon�� ���� ���� ���¸� �Է¹��� ����
		cout << "�Է� �ɺ� epsilon�� ���� ���� ���¸� �Է��� ��, �ڱ� �ڽ��� �Է��ص� �ǰ� ���ص� �˴ϴ�." << endl << endl;

		for (i = 0; i < NFA.state.size(); i++) {

			cout << NFA.state[i] << "�� �Է� �ɺ� epsilon�� ���� ���� ���¸� �Է����ּ���: ";
			getline(cin, nextstate_in_ep);
			NFA.next_state_ep.push_back(nextstate_in_ep);	//�Է¹��� epsilon�� ���� ���� ���¸� NFA.nex_state_ep�� �����Ѵ�
		}
	}

	//���� ���� �Է�
	while (true) {
		cout << endl << "���� ���¸� �Է����ּ���: ";
		getline(cin, NFA.start_state);

		for (i = 0; i < NFA.state.size(); i++) {
			if (NFA.start_state.compare(NFA.state[i]) == 0) {	//�Է¹��� ���� ���°� ������ ���
				goto end_state_input;	//�ٱ��� while���� Ż���Ѵ�
			}
		}
		cout << "�Է��Ͻ� ���°� �������� �ʽ��ϴ�." << endl << "�ٽ� �Է����ּ���." << endl;
	}

	//���� ���� �Է�
end_state_input:
	string end_state_in;	//���� ���¸� �Է¹��� ����

	cout << endl << "���� ���¸� �Է����ּ���. ���� �������� ���°� ������ ��� ����� �������ּ���.";
	getline(cin, end_state_in);

	NFA.end_state = tokenize(end_state_in);	//�Է¹��� ���� ���¸� ���⸦ �������� ��ūȭ�Ͽ� NFA.end_state�� �����Ѵ�

	//���� �Ұ����� ���µ��� ������ DFA ���� ����
	FA DFA;	//������ ���� ���丶Ÿ ����

	DFA.input = NFA.input;	//DFA�� input�� NFA�� input�� ���� �����Ѵ�

	string tmp;	//���ڿ��� tokenize�� ���� ���� ��, ���� ���ڿ��� �ڸ��� �� �ǹǷ� �ӽ÷� ���ڿ��� �����Ͽ� �����صΰų� ��ūȭ�� ���ڿ��� �ٽ� �ϳ��� ��ĥ �� ����� ����
	int cnt = 0;	//DFA�� ������ �� ������ ������ �� ���� ������ ����� ����

	vector<string> tmp_DFA;	//DFA�� ���� ���� ���°� �����Ѵٸ� �� ���µ��� �ӽ÷� �и��Ͽ� ��Ƶ� ����
	vector<string> tmp_next1;	//tmp_DFA�� �и��� ���͵��� ���� ���µ��� �ӽ÷� ��Ƶ� ����
	vector<string> tmp_next2;	//NFA�� DFA�� �ٲ� �� �������� �뵵�� ������ �Խ÷� ������ �� ����� ����

	//�Է¹��� NFA�� epsilon-NFA�� �ƴ϶��
	if (NFA.epsilon_exsist.compare("n") == 0) {

		//DFA�� ���� ���¸� DFA.state�� �����ϰ� ���� ������ ���� ���¸� DFA.next_state�� �ߺ��� ���� �ʴ´ٸ� DFA.state�� ����
		for (i = 0; i < NFA.state.size(); i++) {	//NFA�� ������ ������ŭ �ݺ�
			if (NFA.start_state.compare(NFA.state[i]) == 0) {	//NFA�� ���� ���°� NFA.state[i]���
				DFA.state.push_back(NFA.state[i]);	//DFA�� ù ��° ���·� NFA.state[i]�� ����ִ´�

				for (j = 0; j < DFA.input.size(); j++) {	//DFA�� input�� ������ŭ �ݺ�
					cnt = 0;	//cnt�� 0���� ����

					for (k = 0; k < DFA.state.size(); k++) {	//DFA�� ������ ������ŭ �ݺ�
						if (NFA.next_state[i * DFA.input.size() + j].compare(DFA.state[k]) != 0) {	//NFA�� ���� ������ ���� ���µ��� DFA�� ���µ�� ��ġ�� �ʴ´ٸ�
							cnt++;	//cnt�� 1 ������Ų��
						}
					}

					if (cnt == DFA.state.size()) {	//cnt�� DFA�� ������ ������ ������ �ߺ��� ������ Ȯ�εǾ��ٸ�
						DFA.state.push_back(NFA.next_state[i * DFA.input.size() + j]);	//DFA_state�� NFA�� ���� ������ ���� ���µ��� �߰��Ѵ�
					}
					DFA.next_state.push_back(NFA.next_state[i * DFA.input.size() + j]);	//DFA�� ���� ������ ���� ���µ鿡 NFA�� ���� ������ ���� ���µ��� �߰��Ѵ�
				}

				break;
			}
		}

		//DFA�� ���� ���¸� ������ �ٸ� DFA.state���� �� �Է� �ɹ��� ���� ���� ���¸� DFA.next_state�� �ߺ��� ���� �ʴ´ٸ� DFA.state�� ����
		for (i = 1; i < DFA.state.size(); i++) {	//DFA�� ���� ������ ���� ���µ��� �̹� DFA.next_state�� ������ �ξ����Ƿ� i=0�� ���� ���¸� �����ϰ� i=1���� ����
			tmp_DFA.clear();	//tmp_DFA ���͸� �ʱ�ȭ�Ѵ�
			tmp.assign(DFA.state[i]);	//tmp�� DFA_state[i]�� �ӽ÷� �����صд�
			tmp_DFA = tokenize(tmp);	//tmp_DFA�� tmp�� tokenize�� ���� �����صд�

			if (tmp_DFA.size() == 1) {	//���� DFA.state[i]�� �� ���� ���¶��
				for (j = 0; j < NFA.state.size(); j++) {	//NFA�� ������ ������ŭ �ݺ�
					if (tmp_DFA[0].compare(NFA.state[j]) == 0) {	//tmp_DFA�� ���� ���¸� state���� ã��
						cnt = 0;	//cnt�� 0���� ����

						for (k = 0; k < DFA.input.size(); k++) {	//DFA�� �Է� �ɺ��� ������ŭ �ݺ�
							DFA.next_state.push_back(NFA.next_state[j * DFA.input.size() + k]);	//DFA.next_state�� ���� NFA.state[j]�� next state�� �߰��Ѵ�

							for (l = 0; l < DFA.state.size(); l++) {	//��� DFA.state[]�� ���ϱ� ���Ͽ� DFA.state.size()��ŭ �ݺ�
								if (DFA.state[l].compare(NFA.next_state[j * DFA.input.size() + k]) != 0) {	//������ DFA.next_state�� �߰��� �͵��� DFA_state[l]�� �ߺ����� �ʴ´ٸ�
									cnt++;	//cnt�� 1 ������Ų��
								}
							}

							if (cnt == DFA.state.size()) {	//���� cnt�� DFA_state.size()�� ������ �ߺ��� ������ Ȯ�εǾ��ٸ�
								DFA.state.push_back(NFA.next_state[j * DFA.input.size() + k]);	//DFA_state�� ������ DFA.next_state�� �߰��� �͵��� �߰��Ѵ�
							}
						}
					}
				}
			}

			else {	//���� DFA.state[i]�� ���� ���� ���¶��
				for (a = 0; a < DFA.input.size(); a++) {	//DFA�� �Է� �ɹ��� ������ŭ �ݺ�
					tmp_next1.clear();	//tmp_next1 ���͸� �ʱ�ȭ�Ѵ�
					tmp_next2.clear();	//tmp_next2 ���͸� �ʱ�ȭ�Ѵ�

					//�и��� DFA�� ���� ���� �����ϱ�
					for (j = 0; j < tmp_DFA.size(); j++) {	//DFA.state[i]�� ����Ǿ� �ִ� ������ ������ŭ �ݺ�
						for (k = 0; k < NFA.state.size(); k++) {	//NFA�� ������ ������ŭ �ݺ�
							if (tmp_DFA[j].compare(NFA.state[k]) == 0) {	//state[i]�� �и��� ���°� NFA.state[k]�� ��ġ�Ѵٸ�
								tmp_next1.push_back(NFA.next_state[k * DFA.input.size() + a]);	//NFA.state[k]�� a��° �Է� �ɺ��� ���� ���� ���¸� tmp_next1�� ����
							}
						}
					}

					for (j = 0; j < NFA.state.size(); j++) {	//������� �����ϱ� ���� NFA.state�� j�� 0���� ������Ų��
						cnt = 0;	//�ߺ� ���Ÿ� ���� cnt

						for (k = 0; k < tmp_next1.size(); k++) {	//tmp_next1�� ũ�⸸ŭ �ݺ�
							if ((tmp_next1[k].find(NFA.state[j]) != string::npos) && cnt == 0) {	//tmp_next1[k]�� NFA.state[j]�� �����ϰ� cnt�� ���� 0�̶��
								tmp_next2.push_back(NFA.state[j]);	//NFA.state[j] ���� tmp_next2�� �߰��Ѵ�
								cnt++;	//�ߺ��� ���� tmp_next2�� �߰����� �ʱ� ���Ͽ� cnt�� 1 ������Ų��
							}
						}
					}

					//tmp_next2�� ����� ������ tmp�� ���� �����Ѵ�
					tmp.assign(combine(tmp_next2, NFA.state));

					//tmp�� ���� DFA�� ���µ�� �ߺ����� �ʴ´ٸ�
					cnt = 0;
					for (j = 0; j < DFA.state.size(); j++) {	//tmp�� ���� DFA�� ���µ�� �ߺ��Ǵ��� �˻�
						if (tmp.compare(DFA.state[j]) != 0) {
							cnt++;
						}
					}
					if (cnt == DFA.state.size()) {	//tmp�� ���� DFA�� ���µ�� �ߺ����� �ʴ´ٸ�
						DFA.state.push_back(tmp);	//DFA.state�� tmp ����
					}

					DFA.next_state.push_back(tmp);	//DFA.next_state�� tmp ����
				}
			}
		}

	}	//NFA�� ��� ��

	else if (NFA.epsilon_exsist.compare("y") == 0) {	//epsilon-NFA���

		//DFA.state�� NFA�� ���� ���¸� epsilon_closure�� ���� DFA�� ���� ���¸� ����ִ´�.
		vector<string> tmp_ep;	//epsilon_closure�Լ����� epsilon_closure �Լ��� ����� ������ ����
		epsilon_closure(NFA.state, NFA.next_state_ep, NFA.start_state, tmp_ep);
		DFA.state.push_back(combine(tmp_ep, NFA.state));
		
		for (j = 0; j < DFA.state.size(); j++) {	//DFA�� ������ ������ŭ �ݺ�
			tmp_DFA.clear();	//tmp_DFA �ʱ�ȭ
			tmp.assign(DFA.state[j]);	//tmp�� DFA.state[j]�� ���� �����Ѵ�
			tmp_DFA = tokenize(tmp);	//tmp�� tokenize�� ���� tmp_DFA�� �����Ѵ�

			if (tmp_DFA.size() == 1) {	//���� ���� tmp_DFA�� ������ ���� ���°� 1���� ���¹ۿ� ���ٸ�
				for (k = 0; k < NFA.state.size(); k++) {	//NFA�� ������ ������ŭ �ݺ�
					if (tmp_DFA[0].compare(NFA.state[k]) == 0) {	//���� tmp_DFA�� ����� ���� NFA.state[k]�� ��ġ�Ѵٸ�
						for (a = 0; a < DFA.input.size(); a++) {	//DFA�� �Է� �ɺ��� ������ŭ �ݺ�
							//NFA.next_state[k * DFA.input.size() + a]�� epsilon_closure�� ���� tmp�� �����Ѵ�
							tmp_ep.clear();
							epsilon_closure(NFA.state, NFA.next_state_ep, NFA.next_state[k * DFA.input.size() + a], tmp_ep);
							tmp.assign(combine(tmp_ep, NFA.state));
							
							cnt = 0;	//cnt�� 0���� �����
							for (l = 0; l < DFA.state.size(); l++) {	//DFA�� state�� ������ŭ �ݺ�
								if (tmp.compare(DFA.state[l]) != 0) {	//���� tmp�� DFA.state[l]�� ��ġ���� �ʴ´ٸ�
									cnt++;	//cnt�� 1������Ų��
								}
							}
							if ((cnt == DFA.state.size()) && (tmp != "")) {	//���� cnt�� DFA�� ������ ������ ��ġ�ϰ� tmp�� ������ �ƴ϶��
								DFA.state.push_back(tmp);	//DFA.state�� tmp�� �����Ѵ�
							}
							DFA.next_state.push_back(tmp);	//DFA.next_state�� tmp�� �����Ѵ�
						}
					}
				}
			}

			else {	//���� ���� tmp_DFA�� ������ ���� ���°� 1���� ���º��� ���ٸ�
				for (a = 0; a < DFA.input.size(); a++) {	//DFA.input.size()��ŭ �ݺ�
					tmp_next1.clear();	//tmp_next1�� �ʱ�ȭ
					tmp_next2.clear();	//tmp_next2�� �ʱ�ȭ

					//�и��Ǿ� tmp_DFA�� ����� ������ ���µ��� ���� ���µ��� tmp_next1�� �����Ѵ�
					for (k = 0; k < tmp_DFA.size(); k++) {
						for (l = 0; l < NFA.state.size(); l++) {
							if (tmp_DFA[k].compare(NFA.state[l]) == 0) {
								tmp_next1.push_back(NFA.next_state[l * DFA.input.size() + a]);
							}
						}
					}

					for (k = 0; k < NFA.state.size(); k++) {	//������� �����ϱ� ���� state�� 0���� ������Ų��
						cnt = 0;	//cnt�� 0���� ����

						for (l = 0; l < tmp_next1.size(); l++) {	//tmp_next1�� ũ�⸸ŭ �ݺ�
							if ((tmp_next1[l].find(NFA.state[k]) != string::npos) && cnt == 0) {	//tmp_next1[l]�� NFA.state[k]�� �����ϰ� cnt�� ���� 0�̶��
								tmp_next2.push_back(NFA.state[k]);	//NFA.state[k] ���� tmp_next2�� �߰��Ѵ�
								cnt++;	//�ߺ��� �����ϱ� ���� cnt�� 1 ������Ų��
							}
						}
					}

					tmp.assign(combine(tmp_next2, NFA.state));	//tmp�� tmp_next2�� combine�� ���� �����Ѵ�
					if (tmp_next2.size() == 0) {	//epsilon����� ���� ���°� �����̶��
						DFA.next_state.push_back("");	//DFA.next_state�� ������ �ִ´�
					}

					else {
						//tmp�� epsilon_closure�� ���� tmp�� �����Ѵ�
						tmp_ep.clear();
						epsilon_closure(NFA.state, NFA.next_state_ep, tmp, tmp_ep);
						tmp.assign(combine(tmp_ep, NFA.state));

						cnt = 0;	//cnt�� 0���� �����
						for (l = 0; l < DFA.state.size(); l++) {	//DFA�� state�� ������ŭ �ݺ�
							if (tmp.compare(DFA.state[l]) != 0) {	//���� tmp�� DFA.state[k]�� ��ġ���� �ʴ´ٸ�
								cnt++;	//cnt�� 1������Ų��
							}
						}
						if ((cnt == DFA.state.size()) && (tmp != "")) {	//���� cnt�� DFA�� ������ ������ ��ġ�ϰ� tmp�� ������ �ƴ϶��
							DFA.state.push_back(tmp);	//DFA.state�� tmp�� �����Ѵ�
						}

						DFA.next_state.push_back(tmp);	//DFA.next_state�� tmp�� �����Ѵ�

					}
				}
			}
		}

	}	//epsilon-NFA�� ��� ��

	cout << endl << "���� �Ұ����� ���µ��� ������ DFA" << endl << endl;
	print_state_table(DFA.state, DFA.next_state, DFA.input, DFA.state_transition_function);
	cout << endl;

	//�������� �ʴ� ���µ��� �ϳ��� ��ġ��
	if (DFA.state.size() > 1) {	//DFA.state�� 2�� �̻��� ��� ���� �� �ִ� ���� �ִ��� �˻��Ѵ�

		//DFA�� ���� ���� ã��
		DFA.start_state = DFA.state[0];

		//DFA�� ���� ���� ã��
		for (i = 0; i < DFA.state.size(); i++) {
			for (j = 0; j < NFA.end_state.size(); j++) {
				if (DFA.state[i].find(NFA.end_state[j]) != string::npos) {
					DFA.end_state.push_back(DFA.state[i]);
				}
			}
		}

		vector<int> equivalence;	//������ DFA�� ���¿� ���� ��ġ���� ��ȣ�� ������ ����
		vector<int> equiv_num;	//��ġ���� ��ȣ�� ������ ������ ����

		//�ʱ⿡�� ���� ���¿� ���� ���°� �ƴ� 2���� ��ġ���� ���� ���̹Ƿ� equiv_num�� 0,1,2�� �����Ѵ�
		equiv_num.push_back(0);
		equiv_num.push_back(1);
		equiv_num.push_back(2);
		for (i = 0; i < DFA.state.size(); i++) {	//��� DFA�� ���¸� �˻��Ѵ�
			cnt = 0;

			for (j = 0; j < DFA.end_state.size(); j++) {
				if (DFA.state[i].compare(DFA.end_state[j]) == 0) {	//DFA�� ���°� DFA�� ���� ���¿� ���Ѵٸ�
					equivalence.push_back(equiv_num[2]);	//�ش��ϴ� DFA�� ���¸� ��ġ�� 2�� �����Ѵ�
					cnt++;	//cnt�� 1 ������Ű��
					break;	//���� �ݺ����� Ż���Ѵ�
				}
			}

			if (cnt != 1) {	//���� cnt�� 1�� �ƴ϶��
				equivalence.push_back(equiv_num[1]);	//DFA�� ���°� DFA�� ���� ���¿� ������ �����Ƿ� ��ġ�� 1�� �����Ѵ�
			}
		}

	next_equivalence:
		//�� DFA���� �Է� �ɹ��� ���� � ��ġ���� �̵��Ǵ��� �����ϱ�
		vector<int> equiv_next;	//DFA�� ���°� �Է� �ɹ��� ���� � ��ġ���� �̵��Ǵ��� ������ ����

		for (i = 0; i < DFA.state.size(); i++) {	//DFA�� ������ ������ŭ �ݺ�
			for (j = 0; j < DFA.input.size(); j++) {	//DFA�� �Է� �ɹ��� ������ŭ �ݺ�
				cnt = 0;	//cnt�� 0���� ����

				for (k = 0; k < DFA.state.size(); k++) {	//DFA�� ������ ������ŭ �ݺ�
					if (DFA.next_state[i * DFA.input.size() + j].compare(DFA.state[k]) == 0) {	//DFA.state[i]�� j��° �Է� �ɺ��� ���� ���� ���°� DFA.state[k]�� ��ġ�Ѵٸ�
						equiv_next.push_back(equivalence[k]);	//equiv_next�� state[k]�� ��ġ���� equivalence[k]�� �����Ѵ�
						cnt++;	//cnt�� 1 ������Ų��
					}
				}
				if (cnt == 0) {	//DFA.state[i]�� j��° �Է� �ɺ��� ���� ���� ���°� DFA.state�� ��ġ�ϴ� ���� ���ٸ�
					equiv_next.push_back(0);	//equiv_next�� ��������� ǥ���ϴ� 0�� �����Ѵ�
				}
			}
		}

		for (i = 0; i < equiv_next.size(); i += DFA.input.size()) {	//i�� 0���� DFA�� �Է� �ɹ��� ������ŭ�� ������Ű�� i�� DFA.state[i/input.size()]�� 0��° �Է� �ɹ��� ���� ���� ������ ��ȣ�� ������ �ȴ�
			for (j = i + DFA.input.size(); j < equiv_next.size(); j += DFA.input.size()) {	//j�� i�� ���� ������ ������ DFA.state[i/input.size()]�� �ٷ� ���� ������ DFA.state[(i + DFA.input.size())/input.size()]���� �����Ѵ�
				cnt = 0;	//cnt�� 0���� ����

				for (k = 0; k < DFA.input.size(); k++) {	//DFA�� �Է� �ɹ��� ������ŭ �ݺ�
					if (equiv_next[i + k] == equiv_next[j + k]) {	//���� state[i/input.size()]�� k��° �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� state[j/input.size()]�� k��° �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� ���ٸ�
						cnt++;	//cnt�� 1 ������Ų��
					}
				}

				if (equivalence[i / DFA.input.size()] == equivalence[j / DFA.input.size()] && cnt != DFA.input.size()) {	//���� ��ġ���� ������ �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� ��ȣ�� �ٸ��ٸ�
					if (equiv_num.size() == 3) {	//���� ó������ �ٸ� ���(ó������ �ٸ� ��� ���� equiv_num�� �߰��� ��ȣ�� �����Ƿ� equiv_num�� ũ�Ⱑ ó���� �߰��ߴ� 3�� �״���� ���̴�)
						equiv_num.push_back(3);	//equiv_num�� 3�� �ְ�
						equivalence[j / DFA.input.size()] = equiv_num[3];	//�����Ǵ� ������ ��ġ�� ��ȣ�� 3���� �����Ѵ�

						goto next_equivalence;	//���ο� ��ġ���� �������Ƿ� �� DFA���� �Է� �ɹ��� ���� � ��ġ���� �̵��Ǵ����� �ٽ� �����ؾ� �Ѵ�
					}

					else {	//ó������ �ٸ� ��찡 �ƴ� ���
						for (k = 3; k < equiv_num.size(); k++) {	//k�� 3���� equiv_num�� ����Ǿ� �ִ� ���� ū ��ȣ���� �ݺ�
							for (l = 0; l < equivalence.size(); l++) {	//equivalence�� ũ��(DFA�� ������ ����)��ŭ �ݺ�
								if (equivalence[l] == k) {	//���� l��° state�� ��ġ���� k�� ��ġ�Ѵٸ�
									cnt = 0;	//cnt�� 0���� ����

									for (a = 0; a < DFA.input.size(); a++) {	//DFA�� �Է� �ɹ��� ������ŭ �ݺ�
										if (equiv_next[l * DFA.input.size() + a] == equiv_next[j + a]) {	//���� state[l]�� a��° �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� state[j/input.size()]�� a��° �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� ���ٸ�
											cnt++;	//cnt�� 1 ������Ų��
										}
									}

									if (cnt == DFA.input.size()) {	//cnt�� DFA�� �Է� �ɹ��� ������ ������ ��� �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� ������ Ȯ�εǾ��ٸ�
										equivalence[j / DFA.input.size()] = k;	//state[j/input.size()]�� ��ġ���� k�� �����Ѵ�

										goto next_equivalence;	//��ġ���� �ٲ�����Ƿ� �� DFA���� �Է� �ɹ��� ���� � ��ġ���� �̵��Ǵ����� �ٽ� �����ؾ� �Ѵ�
									}

									else {	//���� �Է� �ɹ��� ���� �̵��Ǵ� ��ġ���� �ٸ��ٸ�
										int num = equiv_num.size();	//equiv_num.size()�� equiv_num�� 0�� ����Ǿ� �ֱ� ������ equiv_num�� ����Ǿ� �ִ� ���� ū ��ȣ���� 1 Ŭ ���̴�
										equivalence[j / DFA.input.size()] = num;	//���� equiv_num�� ����Ǿ� �ִ� ���� ū ��ȣ���� 1 ū ��ȣ�� state[j/DFA.input.size()]�� ��ġ���� ��ȣ�� �����ϰ�
										equiv_num.push_back(num);	//equiv_num�� ����Ǿ� �ִ� ���� ū ��ȣ���� 1 ū ��ȣ�� equiv_num�� �����Ѵ�

										goto next_equivalence;	//���ο� ��ġ���� �������Ƿ� �� DFA���� �Է� �ɹ��� ���� � ��ġ���� �̵��Ǵ����� �ٽ� �����ؾ� �Ѵ�
									}
								}
							}
						}
					}
				}
			}
		}

		cout << "�� DFA�� ���µ��� ��ġ���� ��ȣ" << endl;
		for (i = 0; i < DFA.state.size(); i++) {
			cout << "[" << DFA.state[i] << "]: " << equivalence[i] << endl;
		}

		//���� ���� ���
		cout << endl << "���� ����: " << equivalence[0] << endl;

		//���� ���� ���
		vector<int> tmp_equiv;	//�̹� ����� ���� ���¸� �� ������� �ʱ� ���� �̹� ����� ���� ���¸� �����س��� ����
		tmp_equiv.push_back(0);

		cout << "���� ����: ";
		for (i = 0; i < DFA.state.size(); i++) {
			for (j = 0; j < DFA.end_state.size(); j++) {
				if (DFA.end_state[j].compare(DFA.state[i]) == 0) {	//���� DFA.end_state[j]�� DFA.state[i]�� ��ġ�Ѵٸ�
					cnt = 0;	//cnt�� 0���� ����

					for (k = 0; k < tmp_equiv.size(); k++) {
						if (equivalence[i] == tmp_equiv[k]) {	//tmp_equiv�� �̹� ã�� ���� ���� equivalence[i]�� �ִٸ�
							cnt++;	//cnt�� 1 ������Ų��
						}
					}

					if (cnt == 0) {	//cnt�� 0�̾ �ߺ��� ���� �ʴ´ٸ�
						cout << equivalence[i] << " ";	//ã�� ���� ������ equivalence[i]�� ���
						tmp_equiv.push_back(equivalence[i]);	//�̹� ����� ���� �Ǵٽ� ������� �ʱ� ���� equivalence[i]�� tmp_equiv�� �����Ѵ�
					}
				}
			}
		}
		cout << endl << endl;

		print_state_table_equiv(equivalence, equiv_next, DFA.input, DFA.state_transition_function);

	}	//reduced ��

	return 0;
}

vector<string> tokenize(string s) {	//���ڿ� s�� ���⸦ �������� ��ūȭ�Ͽ� ��ȯ�ϴ� �Լ�
	size_t pos = 0;	//pos�� 0���� �ʱ�ȭ
	string delim = " ";	//����
	vector<string> token;	//s�� ���⸦ �������� ��ūȭ�� ���� ������ ����
	token.clear();

	while ((pos = s.find(delim)) != string::npos) {	//s�� ���� ���� ���µ��� ����ִٸ� 
		token.push_back(s.substr(0, pos));	//���⸦ �������� ��ūȭ�Ͽ� token�� �����Ѵ�
		s.erase(0, pos + delim.length());
	}
	token.push_back(s);	//s�� �� ���� ���°� ����ְų� ���� ���� ���µ��� ������� ���� ������ ���¸� token�� �����Ѵ�

	return token;
}

string combine(vector<string> a, vector<string> state) {	//vector a�� ��� ���ڿ����� �ϳ��� ���� ��ȯ�ϴ� �Լ�
	string s;
	int cnt = 0;
	
	//���� a�� ����Ǿ� �ִ� ������ string s�� ��ĥ ��, ������� ��ġ�� ���ؼ� ���� for���� ����Ѵ�.
	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (a[j].find(state[i]) != string::npos) {
				if (cnt == 0) {	//s�� ���� ó������ ������ ���
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

void epsilon_closure(vector<string> state, vector<string> next_state_ep, string s, vector<string>& tmp_ep) {	//epsilon_closure �Լ�
	vector<string> tmp_ep_closure;	//s�� ��ūȭ�Ͽ� ������ ����

	tmp_ep_closure = tokenize(s);	//s�� ��ūȭ�Ͽ� tmp_ep_closure�� �����Ѵ�

	for (int i = 0; i < tmp_ep_closure.size(); i++) {	//tmp_ep_closure�� ��� ������ ������ŭ �ݺ�
		int cnt = 0;	//cnt�� 0���� ����

		for (int a = 0; a < tmp_ep.size(); a++) {	//tmp_ep�� ũ�⸸ŭ �ݺ�
			if (tmp_ep_closure[i].compare(tmp_ep[a]) == 0) {	//���� tmp_ep_closure[i]�� tmp_ep[a]�� ������
				cnt++;	//cnt�� 1 ������Ų��
			}
		}

		if (cnt == 0) {	//tmp_ep_closure[i]�� tmp_ep[a]�� ������ �߰ߵ��� �ʾ� cnt�� �������� �ʾҴٸ� �ߺ��� ���ٴ� ���̹Ƿ�
			tmp_ep.push_back(tmp_ep_closure[i]);	//tmp_ep_closure[i]�� tmp_ep�� �����Ѵ�

			for (int j = 0; j < state.size(); j++) {	//state�� �����ŭ �ݺ�
				if (tmp_ep_closure[i].compare(state[j]) == 0 && tmp_ep_closure[i].compare(next_state_ep[j]) != 0) {	//���� tmp_ep_closure[i]�� ��ġ�ϴ� state[j]�� �߰��Ͽ��� next_state[j]�� tmp_ep_closure[i]�� ��ġ���� �ʴ´ٸ�
					epsilon_closure(state, next_state_ep, next_state_ep[j], tmp_ep);	//�� state[j]�� epsilon�� ���� ���� ������ next_state_ep[j]�� �Ű� ������ ������ epsilon_closure�Լ� ȣ��
				}
			}
		}
	}
}

void print_state_table(vector<string> state, vector<string> next_state, vector<string> input, string state_transition_function) {	//���� ����ǥ�� ����ϴ� �Լ�
	//�Է� �ɺ� ���
	cout << "  " << state_transition_function << "  ";
	for (int i = 0; i < input.size(); i++) {
		cout << "|   " << input[i] << "   ";
	}
	cout << endl;

	//���µ� ���
	for (int i = 0; i < state.size(); i++) {
		cout << " [" << state[i] << "] ";
		for (int j = 0; j < input.size(); j++) {
			cout << "| [";
			if (next_state[i * input.size() + j].compare("") == 0) {
				cout << "��";
			}
			else {
				cout << next_state[i * input.size() + j];
			}
			cout << "] ";
		}
		cout << endl;
	}
}

void print_state_table_equiv(vector<int> state, vector<int> next_state, vector<string> input, string state_transition_function) {	//�������� �ʴ� ���µ��� �ϳ��� ��ģ �� �ּ�ȭ�� DFA�� ����ϴ� �Լ�
	//�Է� �ɺ� ���
	cout << "  " << state_transition_function << " ";
	for (int i = 0; i < input.size(); i++) {
		cout << "|   " << input[i] << "  ";
	}
	cout << endl;

	vector<int> tmp_int;
	tmp_int.push_back(0);

	//���µ� ���
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
					cout << "��";
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