#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template <typename Value>
class Window {
	protected:
		struct Element {
			Value value;
			int index;
		};

		deque<Element> data;
		const int size;
		function< bool (const Value&, const Value&) > less;
		int last_index = 0;
	public:
		Window (const int& size, function< bool (const Value&, const Value&) > less = std::less<Value>()) :
			size(size), less(less) {}

		Value top () const {
			return data.front().value;
		}

		void push (const Value& value) {
			while (not data.empty() and not less(data.back().value, value))
				data.pop_back();

			data.push_back( {value, ++last_index} );

			if (data.front().index == last_index - size)
				data.pop_front();
		}
};

void optimize_IO () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
}

int main () {
	optimize_IO();

	int T; cin >> T;
	for (; T > 0; --T) {
		int N, M;
		cin >> N >> M;
		vector<int> A(N + 1), B(M + 1);
		for (int index = 1; index <= N; ++index)
			cin >> A[index];
		for (int index = 1; index <= M; ++index)
			cin >> B[index];

		vector<long long> prefix_sum(N + 1);
		prefix_sum[0] = 0;
		for (int index = 1; index <= N; ++index)
			prefix_sum[index] = prefix_sum[index - 1] + A[index];
		auto sum = [&prefix_sum] (const int& begin, const int& end) {
			return prefix_sum[end] - prefix_sum[begin - 1];
		};

		vector<long long> result(N + 1), previous_result(N + 1);
		bool chef_turn = M % 2;

		for (int index = 1; index <= N - B[M] + 1; ++index)
			result[index] = (chef_turn ? +1 : -1) * sum(index, index + B[M] - 1);
		for (int turn = M - 1; turn > 0; --turn) {
			chef_turn = not chef_turn;
			swap(result, previous_result);
			int size = B[turn] - B[turn + 1] - 1;
			Window<long long> candidates (
				size,
				(chef_turn ? (function<bool (const long long&, const long long&)>) less<long long>() : greater<long long>())
			);
			for (int index = 2; index <= size; ++index)
				candidates.push( previous_result[index] );

			for (int index = 1; index <= N - B[turn] + 1; ++index) {
				candidates.push( previous_result[index + size] );
				result[index] = (chef_turn ? +1 : -1) * sum(index, index + B[turn] - 1) + candidates.top();
			}
		}

		cout << *max_element(&result[1], next( &result[N - B[1] + 1] )) << '\n';
	}
}
