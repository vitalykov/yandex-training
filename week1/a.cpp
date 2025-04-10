#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;

    cin >> n >> m;

    vector<int> groups(n + 1, 0);
    vector<int> rooms(m + 1, 0);

    for (size_t i = 1; i < groups.size(); ++i) {
        cin >> groups[i];
        ++groups[i];
    }
    for (size_t i = 1; i < rooms.size(); ++i) {
        cin >> rooms[i];
    }

    vector<size_t> groups_indexes(n + 1);
    iota(groups_indexes.begin(), groups_indexes.end(), 0);
    vector<size_t> rooms_indexes(m + 1);
    iota(rooms_indexes.begin(), rooms_indexes.end(), 0);

    sort(groups_indexes.begin(), groups_indexes.end(), [&groups](size_t i1, size_t i2) {
        return groups[i1] < groups[i2];
    });
    sort(rooms_indexes.begin(), rooms_indexes.end(), [&rooms](size_t i1, size_t i2) {
        return rooms[i1] < rooms[i2];
    });

    int count = 0;
    vector<int> classes(n + 1, 0);
    auto group_it = next(groups_indexes.begin());
    auto room_it = next(rooms_indexes.begin());

    while (group_it != groups_indexes.end() && room_it != rooms_indexes.end()) {
        if (groups[*group_it] <= rooms[*room_it]) {
            ++count;
            classes[*group_it] = *room_it;
            ++group_it;
        }
        
        ++room_it;
    }

    cout << count << endl;

    for (size_t i = 1; i < classes.size() - 1; ++i) {
        cout << classes[i] << ' ';
    }
    cout << classes[n] << endl;

    return 0;
}