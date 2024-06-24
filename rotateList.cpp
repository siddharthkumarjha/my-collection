#include <cstdint>
#include <cstdio>

struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* rotateRight(ListNode* head, int32_t k) 
{
        ListNode *h = head, *l = nullptr;
        // std::ptrdiff_t diff = head - head->next;
        int32_t size = 0;

        while(h != nullptr)
        {
                size++;
                l = h;
                h = h->next;
        }

        h = head;

        l->next = h;

        k %= size;
        int32_t jmp = size - k;

        while(jmp > 1)
        {
                h = h->next;
                jmp--;
        }

        l = h->next;
        h->next = nullptr;

        // while(k >= size)
        // {
        //         k = k - size;
        // }

        // while(k-- > 0)
        // {
        //         l->next = h;
        //         h = l;
        //         l = diff + l;
        //         l->next = nullptr;
        // }
        return l;
}

int main(void)
{
        ListNode *head = new ListNode(1, new ListNode(2, new ListNode(3)));
        ListNode *tmp = head;
        while(tmp != nullptr)
        {
                std::printf("%p -> ", tmp);
                tmp = tmp->next;
        }
        std::printf("%p \n", tmp);
        
        head = rotateRight(head, 4);
        tmp = head;

        while(tmp != nullptr)
        {
                std::printf("%p -> ", tmp);
                tmp = tmp->next;
        }
        std::printf("%p \n", tmp);

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
