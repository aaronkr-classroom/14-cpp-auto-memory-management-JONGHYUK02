// main.cpp
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"
#include "handle.h"
#include "Ref_handle.h"

using namespace std;

bool compare_Core_handles(const Ref_handle<Core>& lhs,
	const Ref_handle<Core>& rhs) {
	return compare(* lhs, * rhs);
}

int main() {
	vector<Handle<Core> > students; // ��ü�� �ƴ� �����͸� ����
	Handle<Core> record;
	char ch;
	string::size_type maxlen = 0;

	// ������ �а� �����ϱ�
	while (cin >> ch) {
		if (cin.eof()) break;  // Check for end of input

		// Handle unexpected empty lines or malformed input
		if (ch != 'U' && ch != 'G') { // g�� �ƴ϶� i�� ����
			// If the input is not a valid student type, skip it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (ch == 'U')
			record = new Core; // Core ��ü �Ҵ�
		else
			record = new Grad; // Grad ��ü �Ҵ�

		// Handle<T>::-> ������ �Լ� ȣ�� �� ���� �Լ� ȣ��
		record->read(cin); 

		maxlen = max(maxlen, record->getName().size()); // ������
		students.push_back(record);
	}

	// �����ͷ� �����ϴ� compare �Լ��� ����
	sort(students.begin(), students.end(), compare_Core_handles);

	// �̸��� ������ ����ϱ�
	for (vector<Handle<Core> >::size_type i = 0;
		i != students.size(); i++) {

		/* Check the type of the student using dynamic_cast
		if (dynamic_cast<Grad*>(students[i])) { //grad�� i�� ����
			// It's a Grad student
			cout << "(G) "; // I�� ����
		}
		else {
			// It's an Undergrad student
			cout << "(U) ";
		}*/


		// �Լ��� ȣ���Ϸ��� �������� students[i]�� ������
		cout << students[i]->getName()
			<< string(maxlen + 1
				- students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade(); // ������
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl; // ���� ���
		}
	}

	return 0;
}