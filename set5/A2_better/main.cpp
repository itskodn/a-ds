#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_set>
#include <cmath>

#include "stream.h"
#include "hyperloglog.h"
#include "hyperloglog_optimized.h"

struct StepResult {
    int step, processed, exact_f0;
    double est_std, est_packed;
};

std::vector<StepResult> run_stream( const std::vector<std::string>& stream, HashFuncGen::HashFunc& hf,
    int B, const std::vector<int>& steps) {
    HyperLogLog hll(B);
    HyperLogLogOptimized hll_p(B);
    std::unordered_set<std::string> seen;
    std::vector<StepResult> res;
    int prev = 0;
    for (int k = 0; k < (int)steps.size(); k++) {
        int up_to = steps[k];
        for (int i = prev; i < up_to; i++) {
            uint32_t h = hf(stream[i]);
            hll.add(h);
            hll_p.add(h);
            seen.insert(stream[i]);
        }
        prev = up_to;
        res.push_back({k+1, up_to, (int)seen.size(), hll.estimate(), hll_p.estimate()});
    }
    return res;
}

int main() {
    const int B = 14;
    const int num_streams = 30;
    const int stream_size = 1000000;
    const int step_pct = 2;    
    auto steps = RandomStream::partition(stream_size, step_pct);
    int num_steps = steps.size();

    std::vector<std::vector<StepResult>> all(num_streams);
    HashFuncGen hfg(777);

    for (int s = 0; s < num_streams; s++) {
        RandomStream gen(stream_size, 1000 + s * 37);
        auto stream = gen.generate();
        auto hf = hfg.generate();
        all[s] = run_stream(stream, hf, B, steps);
    }
    std::ofstream f_single("single_stream.csv");
    f_single << "step,processed,exact_f0,hll_std,hll_packed\n";
    f_single << std::fixed << std::setprecision(1);
    for (const auto& r : all[0]) {
        f_single << r.step << "," << r.processed << "," << r.exact_f0 << "," << r.est_std << ","<< r.est_packed << "\n";
    }

    std::ofstream f_stats("statistics.csv");
    f_stats << "step,processed,mean_f0,mean_std,std_std,mean_packed,std_packed\n";
    f_stats << std::fixed << std::setprecision(1);
    for (int si = 0; si < num_steps; si++) {
        double sf0=0, ss=0, sp=0;
        for (int s = 0; s < num_streams; s++) {
            sf0+= all[s][si].exact_f0;
            ss+= all[s][si].est_std;
            sp+= all[s][si].est_packed;
        }
        double mf0 = sf0/num_streams;
        double ms = ss/num_streams;
        double mp = sp/num_streams;
        double vs=0, vp=0;
        for (int s = 0; s < num_streams; s++) {
            double d1 = all[s][si].est_std - ms;
            vs+= d1*d1;
            double d2 = all[s][si].est_packed - mp;
            vp+= d2*d2;
        }
        f_stats << si+1 << "," << all[0][si].processed << "," << mf0 << "," << ms << "," << sqrt(vs/num_streams) << "," << mp << "," << sqrt(vp/num_streams) << "\n";
    }

    std::ofstream f_b("b_comparison.csv");
    f_b << "B,m,rel_error\n";
    f_b << std::fixed << std::setprecision(6);
    RandomStream gen(stream_size, 999);
    auto stream = gen.generate();
    std::unordered_set<std::string> seen(stream.begin(), stream.end());
    int exact = seen.size();
    HashFuncGen hfg2(555);
    for (int b = 4; b <= 16; b++) {
        auto hf = hfg2.generate();
        HyperLogLog hll(b);
        for (int i = 0; i < stream_size; i++) {
            hll.add(hf(stream[i]));
        }
        double est = hll.estimate();
        double rel = fabs(est - exact) / exact;
        f_b << b << "," << (1<<b) << "," << rel << "\n";
    }

    return 0;
}
