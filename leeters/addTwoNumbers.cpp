class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Initialize result list
        ListNode dummy(0);
        // Initialize tail to point to dummy starting snode
        ListNode* tail = &dummy;

        // Initialize carry
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry !=0) {
            int val1 = l1 != nullptr ? l1->val : 0;
            int val2 = l2 != nullptr ? l2->val : 0;

            int sum = val1 + val2;
            int digit = sum % 10;
            carry = sum / 10;

            tail->next = new ListNode(digit);
            tail = tail->next;

            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }

        }

        return dummy.next;

    };
};