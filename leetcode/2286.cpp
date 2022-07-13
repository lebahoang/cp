#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

// g++ -std=c++17 -Wshadow -Wall -o s.out -O2 -Wno-unused-result -g -fsanitize=address -fsanitize=undefined 2286.cpp && ./s.out
using namespace std;
using ll = long long;
using getTwoNodeValueFunc = ll (*)(ll a, ll b);
using updateOneNodeValueFunc = ll (*)(ll a, ll b);

const ll NEG_INF = -1e18;
ll getAdd(ll a, ll b) {
    // printf("qqqqq %lld %lld\n", a, b);
    if (b == NEG_INF || a == NEG_INF) return NEG_INF;
    return a+b;
}

ll getMax(ll a, ll b) {
    // printf("qqqqq %lld %lld\n", a, b);
    if (b == NEG_INF || a == NEG_INF) return NEG_INF;
    return max(a, b);
}

ll updateAdd(ll a, ll b) {
    if (b == NEG_INF || a == NEG_INF) return NEG_INF;
    return a+b;
}


struct Row {
    int rem;
};
class LazySegmentTree {
private:
    int numItems;
    vector<ll> tree;
    vector<ll> lazy;
    getTwoNodeValueFunc getFunc;
    updateOneNodeValueFunc updateFunc;

    int getNumberOfNodes() {
        int x = int(ceil(log2(numItems)));
        return ((1-pow(2, x+1))/(1-2)) + 1;
    };
    void buildTree() {
        vector<ll> t1(getNumberOfNodes(), 0);
        tree = t1;
        vector<ll> t2(getNumberOfNodes(), 0);
        lazy = t2;
    };
    void _update(ll value, int ind, int start, int end, int l, int r) {
        // update value of 1 node in tree
        // [start, end] is an updating index interval of segment tree
        // [l, r] is user input index interval
        if (lazy[ind] != 0) {
            if (lazy[ind] == NEG_INF) {
                tree[ind] = 0;
            } else {
                tree[ind] = updateFunc(tree[ind], (end - start + 1) * lazy[ind]);
            }
            
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }    
            lazy[ind] = 0;
        }
            
        if (start > r || end < l) return;
        if (start >= l && end <= r) {
            if (value == NEG_INF) {
                tree[ind] = 0;
            } else {
                tree[ind] = updateFunc(tree[ind], (end - start + 1) * value);
            }
            
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], value);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], value);
            }
            return;
        }
            
        int mid = (start+end)/2;
        _update(value, 2*ind+1, start, mid, l, r);
        _update(value, 2*ind+2, mid+1, end, l, r);
        tree[ind] = getFunc(tree[2*ind+1], tree[2*ind+2]);
    };
    
    ll _query(int ind, int start, int end, int l, int r) {
        if (lazy[ind] != 0) {
            if (lazy[ind] == NEG_INF) {
                tree[ind] = 0;
            } else {
                tree[ind] = updateFunc(tree[ind], (end - start + 1) * lazy[ind]);
            }
            if (start != end) {
                lazy[2*ind+1] = updateFunc(lazy[2*ind+1], lazy[ind]);
                lazy[2*ind+2] = updateFunc(lazy[2*ind+2], lazy[ind]);
            }
            lazy[ind] = 0;
        }
            
        if (start > r || end < l) return NEG_INF;

        if (start >= l && end <= r) return tree[ind];

        int mid = (start + end)/2;
        ll a = _query(2*ind+1, start, mid, l, r);
        ll b = _query(2*ind+2, mid+1, end, l, r);
        if (a == NEG_INF) return b;
        else if (b == NEG_INF) return a;
        return getFunc(a, b);
    };
public:
    LazySegmentTree(int numItemsx, getTwoNodeValueFunc get, updateOneNodeValueFunc update) {
        numItems = numItemsx;
        getFunc = get;
        updateFunc = update;
        buildTree();
    };
    void update(ll value, int l, int r) {
        return _update(value, 0, 0, numItems-1, l, r);
    };
    ll query(int l, int r) {
        return _query(0, 0, numItems-1, l, r);
    };
};


class BookMyShow {
private:
    int n;
    int m;
    vector<Row> r;
    LazySegmentTree* treeMax;
    LazySegmentTree* treeSum;
public:
    void pp() {
        for (int i = 0; i < n; i++) {
            printf("I %d %lld %lld\n", i, treeMax->query(i,i), treeSum->query(i,i));
        }
        printf("-------\n");
    }
    int bs1(ll k, int s, int e) {
        ll val = treeMax->query(0, e);
        if (val < k) return -1;
        val = treeMax->query(0, 0);
        if (val >= k) return 0;
        vector<int> prs = {};
        int a = s;
        int b = e;
        while (a <= b) {
            int mid = (a+b)/2;
            val = treeMax->query(0, mid);
            printf("BS1 mid %d val %lld\n", mid, val);
            if (val >= k) {
                ll valPrev = treeMax->query(0, mid-1);
                printf("BS1 [mid-1] %d valPrev %lld\n", mid-1, valPrev);
                if (valPrev < k) {
                    return mid;
                } else {
                    b = mid-1;
                }
            } else {
                a = mid+1;
            }
        }
        return -1;
    }
    pair<int, ll> bs2(ll k, int s, int e) {
        ll val = treeSum->query(0, e);
        printf("BS2 a %d b %d VAL %lld\n", 0, e, val);
        if (val < k) return {-1, -1};
        val = treeSum->query(0, 0);
        printf("BS2 a %d b %d VAL %lld\n", 0, 0, val);
        if (val >= k) return {0, k};
        int a = s;
        int b = e;
        while (a <= b) {
            int mid = (a+b)/2;
            val = treeSum->query(0, mid);
            printf("BS2 a %d b %d search [0-%d] VAL %lld\n", a, b, mid, val);
            if (val >= k) {
                ll valPrev = treeSum->query(0, mid-1);
                if (valPrev < k) {
                    return {mid, k-valPrev};
                } else if (valPrev >= k) {
                    b = mid-1;
                }
            } else {
                a = mid+1;
            }
        }
        return {-1, -1};
    }
    BookMyShow(int nx, int mx) {
        // LazySegmentTree treex(n, (getTwoNodeValueFunc)getAdd, (updateOneNodeValueFunc)updateAdd);
        n = nx;
        m = mx;
        treeMax = new LazySegmentTree(n, (getTwoNodeValueFunc)getMax, (updateOneNodeValueFunc)updateAdd);
        treeSum = new LazySegmentTree(n, (getTwoNodeValueFunc)getAdd, (updateOneNodeValueFunc)updateAdd);
        r = {};
        for (int i = 0; i < n; i++) {
            r.push_back(Row{(ll)0});
            ll val = (ll)m;
            treeMax->update(val, i, i);
            treeSum->update(val, i, i);
        }
    }
    
    vector<int> gather(int k, int maxRow) {
        ll kk = (ll)k;
        int i = bs1(kk, 0, maxRow);
        printf("Gather K %d, maxRow %d, I %d\n", k, maxRow, i);
        if (i == -1) return vector<int>{};
        treeMax->update(-kk, i, i);
        treeSum->update(-kk, i, i);
        vector<int> rs = {i, r[i].rem};
        r[i].rem += k;
        printf("Gather\n");
        pp();
        return rs;
    }
    
    bool scatter(int k, int maxRow) {
        ll kk = (ll)k;
        pair<int, ll> i = bs2(kk, 0, maxRow);
        int ind = i.first;
        ll val = i.second;
        printf("Scatter K %d, maxRow %d, I %d val %lld\n", k, maxRow, ind, val);
        if (ind == -1) return false;
        if (ind > 0) {
            treeMax->update(NEG_INF, 0, ind-1);
            treeSum->update(NEG_INF, 0, ind-1);
        }
        treeMax->update(-val, ind, ind);
        treeSum->update(-val, ind, ind);
        r[ind].rem += (int)val;
        printf("Scatter\n");
        pp();
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */

int main() {
    vector<string> cmds = {"BookMyShow","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","gather","gather","scatter","gather","gather","scatter","gather","scatter","scatter","scatter","scatter","scatter","scatter","scatter","scatter","gather","scatter","gather","gather","scatter","gather","scatter","gather","gather","scatter","scatter","gather","gather","gather","gather","scatter","gather","scatter","scatter","scatter","scatter","scatter","gather","scatter","scatter","scatter","scatter","gather","scatter","scatter","scatter","scatter","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","scatter","scatter","scatter","gather","gather","scatter","gather","scatter","scatter","scatter","gather","gather","gather","gather","gather","gather","gather","gather","scatter","gather","gather","scatter","gather","gather","scatter","scatter","scatter","scatter","scatter","gather","scatter","gather","gather","gather","gather","scatter","scatter","scatter","gather","gather","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","gather","gather","scatter","scatter","gather","gather","scatter","scatter","gather","gather","scatter","scatter","scatter","scatter","scatter","scatter","gather","gather","scatter","scatter","scatter","scatter","gather","scatter","gather","scatter","scatter","scatter","gather","gather","gather","gather","scatter","scatter","gather","gather","scatter","scatter","gather","scatter","scatter","gather","gather","scatter","gather","scatter","gather","gather","scatter","scatter","gather","gather","scatter","gather","scatter","scatter","gather","gather","gather","gather","gather","scatter","gather","scatter","scatter","gather","gather","gather","gather","scatter","gather","gather","scatter","gather","scatter","scatter","scatter","gather","gather","gather","scatter","scatter","gather","gather","gather","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","gather","scatter","scatter","scatter","scatter","scatter","gather","scatter","scatter","gather","gather","gather","gather","scatter","gather","scatter","gather","gather","scatter","scatter","gather","scatter","scatter","scatter","gather","gather","gather","scatter","scatter","scatter","gather","scatter","scatter","scatter","scatter","gather","scatter","scatter","gather","gather","gather","gather","gather","scatter","gather","scatter","scatter","gather","gather","gather","gather","gather","gather","scatter","gather","gather","scatter","scatter","gather","gather","gather","scatter","scatter","scatter","scatter","gather","gather","scatter","gather","scatter","gather","gather","gather","gather","scatter","scatter","gather","scatter","gather","gather","scatter","gather","scatter","scatter","scatter","scatter","scatter","scatter","scatter","scatter","gather","gather","scatter","scatter","gather","gather","scatter","gather","scatter","gather","scatter","gather","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","gather","scatter","gather","gather","gather","gather","scatter","gather","scatter","scatter","scatter","gather","gather","gather","gather","gather","scatter","gather","scatter","gather","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","gather","gather","scatter","scatter","scatter","gather","gather","scatter","scatter","gather","gather","scatter","gather","scatter","scatter","gather","gather","scatter","gather","scatter","gather","scatter","gather","scatter","gather","scatter","scatter","gather","scatter","gather","scatter","scatter","scatter","scatter","gather","scatter","gather","gather","scatter","gather","gather","scatter","gather","scatter","scatter","gather","gather","gather","scatter","scatter","scatter","gather","gather","gather","scatter","scatter","gather","scatter","gather","scatter","scatter","scatter","gather","gather","scatter","scatter","gather","gather","gather","scatter","scatter","scatter","scatter","gather","gather","gather","gather","gather","scatter","gather","gather","gather","gather","gather","gather","gather","scatter","scatter","scatter","gather","gather","gather","gather","gather","gather","gather","gather","scatter","gather","scatter","scatter","gather","scatter","scatter","gather","scatter","scatter","scatter","gather","scatter","scatter","gather","gather","gather","gather","scatter","scatter","scatter","scatter","gather","scatter","gather","gather","gather","scatter","scatter","scatter","scatter","scatter","gather","scatter","gather","scatter","scatter","scatter","gather","scatter","scatter","scatter","gather","gather","gather","gather","gather","gather","scatter","gather","gather","gather","scatter","gather","scatter","scatter","gather","scatter","scatter","scatter","scatter","gather","scatter","scatter","scatter","scatter","gather","gather","gather","scatter","scatter","gather","scatter","scatter","scatter","gather","scatter"};
    vector<vector<int>> cmdVals = {{582,960777201},{855976634,336},{897802230,416},{436989303,309},{74321550,553},{757919793,408},{281511364,114},{875680813,510},{708945871,238},{228838878,300},{928595053,510},{773153601,384},{274385949,298},{341429529,575},{737937855,377},{711653494,75},{761921266,407},{214720481,115},{383057062,116},{301478478,420},{52590664,161},{61117712,208},{993045550,478},{860753526,34},{911913759,422},{136691632,116},{769561964,339},{64523564,524},{717144828,283},{67822654,151},{618581793,224},{537519599,474},{174077407,376},{111873580,373},{456703857,506},{271465968,481},{187033784,203},{163528014,407},{354777324,40},{652530019,382},{533913892,369},{495415306,529},{617102962,238},{493924696,385},{100102828,577},{677232625,55},{117321775,475},{82333285,46},{315015405,179},{652797104,572},{995034561,319},{173767620,102},{238955982,299},{910433401,142},{701426819,480},{102064838,560},{882782109,462},{228619146,139},{530643511,186},{660572308,0},{558863286,19},{441818683,279},{989097584,5},{396618115,137},{494296172,8},{668850458,501},{507721570,361},{46567990,171},{407343144,27},{745134092,534},{976987369,136},{411342131,222},{44688923,223},{708909187,39},{343767648,184},{13212278,533},{933269532,106},{287484023,513},{325775899,316},{959840912,295},{676086853,188},{678123456,369},{856091491,514},{470319625,335},{244700310,136},{873242489,541},{477531341,517},{150814880,285},{543219983,195},{74718613,287},{968506161,530},{948089724,53},{182293203,155},{878244738,538},{632100434,237},{307225396,209},{12300232,367},{431873092,408},{943124384,298},{221675024,422},{365186500,468},{513190854,433},{661069912,539},{463080855,408},{943412207,302},{38543245,390},{357483448,560},{421922326,31},{181881328,340},{842224315,162},{947372709,298},{452348715,147},{364401597,455},{693202818,163},{179796352,132},{861612208,121},{845785860,493},{133486060,213},{42213276,431},{135022158,408},{51316470,88},{427124237,304},{593293204,246},{661147934,301},{864796391,144},{846495068,154},{409632479,394},{608621619,255},{232743386,22},{725749773,527},{240660460,301},{78137061,451},{89677914,111},{73050404,17},{763237503,166},{811325555,505},{900747103,113},{101942165,395},{269113464,375},{562333866,395},{928612418,520},{271961153,503},{239683114,21},{770528307,113},{152894529,75},{623514570,101},{613136905,449},{416049929,504},{713180349,556},{567933732,168},{487921666,270},{420138402,118},{541914822,328},{198975074,367},{305298064,51},{248599081,330},{260667168,107},{382740677,452},{317693930,499},{876780954,154},{405798727,433},{176923086,227},{42349158,139},{721363197,175},{786588016,152},{306596299,65},{288563546,381},{142281570,366},{650003330,470},{736096039,314},{320047383,179},{769329782,203},{890094469,567},{545796884,220},{700507143,512},{123998124,397},{927324296,2},{447062200,353},{356160648,286},{915522163,380},{862420612,340},{116716333,506},{208666603,183},{866400512,216},{44123779,93},{819462371,104},{87400522,407},{971891559,496},{451294787,223},{371155355,277},{211723663,569},{593416362,318},{727750484,513},{586098435,217},{692246282,427},{956706452,337},{81940036,263},{413519948,163},{364512917,578},{545023689,375},{191228076,332},{477838574,185},{610137531,451},{254789040,490},{408307359,15},{752978454,506},{765882570,278},{259041403,266},{326306723,109},{327579969,372},{812011347,365},{584580661,326},{930402586,187},{68228178,435},{474013143,374},{316225352,250},{479127135,380},{119825847,117},{458298920,429},{509943617,314},{58982863,47},{168192090,123},{846372988,386},{714684915,36},{751417923,223},{140749455,238},{640978581,542},{621437501,371},{563169730,413},{943288669,493},{33836980,284},{75714016,104},{976287504,469},{473952535,366},{217912406,181},{654656797,18},{294113236,423},{68790391,441},{823336485,233},{446841694,345},{737708444,266},{377273987,292},{473125218,536},{249175692,116},{717672979,378},{294032090,211},{968682443,564},{941093600,557},{113771320,44},{201974976,310},{621087788,6},{16449951,256},{363760573,507},{401175008,236},{713592013,572},{419466626,218},{339237908,553},{368054913,476},{283664842,296},{574878379,94},{150174713,25},{484838310,277},{942750859,432},{85998837,284},{510323713,228},{633324776,116},{662942605,157},{638884885,94},{218872197,25},{891690143,55},{681143057,231},{777303707,129},{49389881,28},{75793814,245},{933931897,373},{809642591,437},{542454708,210},{711043150,168},{903655418,570},{347737636,520},{298138742,59},{893138039,468},{993821215,338},{31375269,198},{783314141,520},{558019357,36},{908106705,201},{308345332,184},{958833679,553},{632429692,71},{402312854,111},{239064536,372},{684685398,475},{399349580,226},{394513499,474},{216680482,397},{925283373,303},{790153927,180},{525221683,240},{292249284,162},{197536995,295},{228201240,329},{320431869,536},{232115253,555},{798784410,549},{658723608,33},{545580124,275},{339848201,236},{995466953,129},{463932914,371},{59312601,243},{28015261,413},{398268771,279},{513789302,275},{919386911,504},{471523775,399},{961368147,573},{341827797,399},{214363510,50},{727994051,360},{898565355,307},{903272728,170},{595823377,377},{943648485,535},{150889413,422},{118479623,160},{548208622,349},{462641360,2},{988373536,236},{665285377,365},{642835079,129},{231419876,480},{487054415,402},{177094096,293},{749984093,557},{658940548,170},{787166955,568},{205089971,101},{970894656,295},{662130296,439},{876431340,524},{738911779,552},{589613511,223},{175784740,457},{611059645,326},{872834521,70},{103493062,346},{503290155,338},{425118418,79},{811951335,143},{561847249,347},{684231021,544},{538619929,289},{706823134,526},{481285315,566},{828210731,73},{434299892,309},{454076517,186},{4526775,100},{720520510,298},{634021008,236},{722744497,96},{988395692,580},{913716180,387},{414504905,545},{881078954,395},{20357524,369},{336179594,17},{346317521,245},{41918111,33},{190675407,544},{834067055,207},{932772960,225},{283645916,353},{608153494,85},{384370619,204},{355223244,139},{576358232,388},{657623327,303},{655994223,87},{132230567,408},{479262427,579},{189511437,231},{746415455,189},{955463927,455},{311476778,492},{751220698,526},{125431303,96},{164582740,238},{929502207,452},{457011140,227},{641068059,75},{795934758,149},{837946030,107},{289287291,63},{446057533,434},{429241138,488},{246619913,499},{686871168,355},{852492798,152},{25506043,9},{81613643,80},{906469630,374},{603179523,136},{213970447,442},{13943677,569},{402836300,181},{599102441,337},{52811962,23},{802027213,128},{11278978,163},{415423920,274},{183552043,239},{914335580,412},{621712427,467},{84357875,188},{850540988,346},{295699619,129},{987787528,169},{223477240,479},{775205321,369},{962351048,414},{664931845,45},{506015154,221},{396991260,503},{761537620,386},{885170279,214},{842351142,247},{188557261,153},{863818624,273},{176585999,408},{135189272,216},{738531564,419},{448663499,205},{212018754,362},{901942950,61},{431263129,538},{319084510,15},{283603715,280},{854748057,236},{611804036,336},{570587732,138},{66008548,304},{66954841,38},{558101096,192},{311610803,402},{605967950,221},{87714365,46},{621299414,236},{611667888,268},{843535311,175},{842163769,552},{66132288,56},{661344529,445},{54493464,251},{376077527,574},{49913883,385},{936866441,125},{303416992,173},{815888517,386},{940705537,68},{635206403,116},{377376839,282},{98851646,103},{375332675,285},{832430148,401},{450362821,200},{483488239,457},{264117687,308},{765391936,449},{55851860,508},{294394561,20},{949510428,426},{629795828,180},{78848547,168},{6486214,289},{417125067,537},{622502011,561},{395897693,394},{338049585,3},{417435801,206},{275038958,355},{348058406,160},{894743670,572},{514233421,100},{782216189,524},{153573398,284},{464041688,481},{892228965,24},{323024777,284},{243885775,139},{343092688,513},{255895602,341},{688447610,12},{799549528,570},{942358314,133},{249231467,455},{606182487,75},{562696008,124},{849312503,390},{787256721,242},{765349982,246},{791045246,503},{214286234,457},{295318944,436},{384042583,214},{699178572,289},{690668031,209},{788998240,211},{793567721,54},{209169510,304},{794508324,150},{274867695,90},{999646852,319},{185911398,286},{617446775,162},{537628571,124},{727142077,502},{784104295,255},{16553419,315},{836848589,522},{575270554,285},{512217298,304},{285716546,138},{67672220,276},{918050706,164},{966388734,532},{118236690,53},{393753760,577},{664293842,516},{797275306,397}};
    int n = cmdVals[0][0];
    int m = cmdVals[0][1];
    BookMyShow* obj = new BookMyShow(n, m);
    for (int i = 1; i < (int)cmds.size(); i++) {
        if (cmds[i] == "gather") {
            printf("Gather [%d %d]\n", cmdVals[i][0], cmdVals[i][1]);
            vector<int> param_1 = obj->gather(cmdVals[i][0], cmdVals[i][1]);
            if ((int)param_1.size() > 0) printf("[%d, %d]\n", param_1[0], param_1[1]);
            else printf("[]\n");
        } else {
            printf("Scatter [%d %d]\n", cmdVals[i][0], cmdVals[i][1]);
            bool param_2 = obj->scatter(cmdVals[i][0], cmdVals[i][1]);
            if (param_2) printf("true\n");
            else printf("false\n");
        }
    }
    return 0;
}
