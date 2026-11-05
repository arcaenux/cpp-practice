//
// Created by Arcaenux on 05/11/2026.
//
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {

            for (int j = 0; j < nums.size(); j++) {

                if ( i != j) {
                    int sum = nums[i] + nums[j];
                    if (sum == target) {
                        return {i, j};
                    }
                }
            }
        }
        return {};
    }
};


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> myMap;

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if ( myMap.find(complement) != myMap.end()) {
                return {myMap[complement], i};
            }
            myMap[nums[i]] = i;
        }
        return {};
     }
}