class Solution {
public:
    void pp(vector<int>& a) {
        printf("Arr:");
        for (int x: a) {
            printf("%d ", x);
        }
        printf("\n");
    }
    void generate_3sets(vector<int>& a, int i, int n, vector<int>& rs1, vector<int>& rs2, vector<int>& rs3) {
        if (i == n) {
            pp(rs1);
            pp(rs2);
            pp(rs3);
            printf("-------\n");
            return;
        };
        rs1.push_back(a[i]);
        generate_3sets(a, i+1, n, rs1, rs2, rs3);
        rs1.pop_back();
        rs2.push_back(a[i]);
        generate_3sets(a, i+1, n, rs1, rs2, rs3);
        rs2.pop_back();
        rs3.push_back(a[i]);
        generate_3sets(a, i+1, n, rs1, rs2, rs3);
        rs3.pop_back();
    }
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        int rs = 0;
        vector<int> a = {};
        vector<int> b = {};
        vector<int> c = {};
        vector<int> arr = {1,2,3};
        generate_3sets(arr, 0, 3, a, b, c);
        return rs;
    }
};