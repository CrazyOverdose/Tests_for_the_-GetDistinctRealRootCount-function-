#include "pch.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

template <class T>   // вывод вектора
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>  // вывод сета
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>  // вывод мэпа
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>    // проверка на равенство и кидание исплючения, если не совпало 
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) { // переопределение ассерта
	AssertEqual(b, true, hint);
}

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a == 0) {
		if (b == 0)
			return 0;
		return 1;
	}
	else if (b == 0) {
		if (c == 0)				
			return 1;
	}
	return 2;
}

void a_equals_0_and_b_equals_0() {

	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "a_equals_0_and_b_equals_0. Line 84");
	AssertEqual(GetDistinctRealRootCount(0, 0, -3), 0, "a_equals_0_and_b_equals_0. Line 85");
}

void a_equals_0_and_c_equals_0() {

	AssertEqual(GetDistinctRealRootCount(0, 9, 0), 1, "a_equals_0_and_c_equals_0. Line 90");
	AssertEqual(GetDistinctRealRootCount(0, -5, 0), 1, "a_equals_0_and_c_equals_0. Line 91");
}

void b_equals_0_and_c_equals_0() {

	AssertEqual(GetDistinctRealRootCount(4, 0, 0), 1, "b_equals_0_and_c_equals_0. Line 96");
	AssertEqual(GetDistinctRealRootCount(-2, 0, 0), 1, "b_equals_0_and_c_equals_0. Line 97");
}

void a_equals_0() {

	AssertEqual(GetDistinctRealRootCount(0, 3, 4), 1, "a_equals_0. Line 102");
	AssertEqual(GetDistinctRealRootCount(0, -2, -2), 1, "a_equals_0. Line 103");
	AssertEqual(GetDistinctRealRootCount(0, -2, 3), 1, "a_equals_0. Line 104");
	AssertEqual(GetDistinctRealRootCount(0, 7, -2), 1, "a_equals_0. Line 105");
}

void b_equals_0() {
	AssertEqual(GetDistinctRealRootCount(4, 0, -1), 2, "b_equals_0. Line 109");
	AssertEqual(GetDistinctRealRootCount(-2, 0, 9), 2, "b_equals_0. Line 110");
	AssertEqual(GetDistinctRealRootCount(2, 0, 9), 0, "b_equals_0. Line 111");
	AssertEqual(GetDistinctRealRootCount(-2, 0, -9), 0, "b_equals_0. Line 112");
}

void c_equals_0() {
	AssertEqual(GetDistinctRealRootCount(4, 3, 0), 2, "c_equals_0. Line 116");
	AssertEqual(GetDistinctRealRootCount(-2, -2, 0), 2, "c_equals_0. Line 117");
	AssertEqual(GetDistinctRealRootCount(4, -9, 0), 2, "c_equals_0. Line 118");
	AssertEqual(GetDistinctRealRootCount(-2, 8, 0), 2, "c_equals_0. Line 119");
}


class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};


void AllTest(TestRunner& test) {

	test.RunTest(a_equals_0_and_b_equals_0, "a_equals_0_and_b_equals_0");
	test.RunTest(a_equals_0_and_c_equals_0, "a_equals_0_and_c_equals_0");
	test.RunTest(b_equals_0_and_c_equals_0, "b_equals_0_and_c_equals_0");
	test.RunTest(a_equals_0, "a_equals_0");
	test.RunTest(b_equals_0, "b_equals_0");
	test.RunTest(c_equals_0, "c_equals_0");
}


int main() {
	TestRunner runner;
	AllTest(runner);
	return 0;
}
