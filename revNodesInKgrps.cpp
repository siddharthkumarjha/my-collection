/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <cstdint>
#include <cstdio>
#include <vector>

struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
        public:
                ListNode* reverseKGroup(ListNode* head, int k);
};

ListNode* Solution::reverseKGroup(ListNode* head, int k) 
{
        if(head == nullptr)
                return head;

        ListNode *tmp = head;
        uint32_t size = 0;
        while(tmp != nullptr)
        {
                size++;
                tmp = tmp->next;
        }
        size = size - (size % k);

        ListNode *next = nullptr;
        ListNode *prev = nullptr, *cur = head;

        int kClone = k;
        std::vector<ListNode *>vec;
        std::vector<std::ptrdiff_t> vdiff;

        while(size > 0)
        {
                kClone = k;
                tmp = cur;
                while(kClone > 0)
                {
                        next = cur->next;
                        cur->next = prev;
                        prev = cur;
                        cur = next;
                        kClone--;
                }
                vec.push_back(prev);
                vdiff.push_back(prev - tmp);
                size = size - k;
                prev = nullptr;
        }
        if(cur != nullptr)
                vec.push_back(cur);

        uint32_t n = vec.size() - 1;
        for(uint32_t i = 0; i < n; i++)
        {
                ListNode *h = vec[i] - vdiff[i];
                h->next = vec[i+1];
        }
        return vec[0];
}

int main(void)
{
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
        ListNode *tmp = head;
        while(tmp != nullptr)
        {
                std::printf("%d -> ", tmp->val);
                tmp = tmp->next;
        }
        std::printf("nullptr\n");
        
        Solution obj;
        head = obj.reverseKGroup(head, 2);
        tmp = head;

        while(tmp != nullptr)
        {
                std::printf("%d -> ", tmp->val);
                tmp = tmp->next;
        }
        std::printf("nullptr\n");

        //GC
        while(head != nullptr)
        {
                tmp = head;
                head = head->next;
                delete tmp;
                tmp = nullptr;
        }
        return 0;
}
