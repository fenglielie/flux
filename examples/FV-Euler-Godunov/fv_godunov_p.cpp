#include "fv_test.hpp"
#include "period_index.hpp"
#include "solver/solver_template.hpp"

using namespace flux;  // NOLINT
using flux::solver_template::EulerUpdater;
using flux::solver_template::OpNull;
using flux::solver_template::Solver;

struct GetDt {
    double operator()(const Vec &var, Mesh1d &ex, double t) const {
        const auto &u = var.data;
        double df_max = 0;
        for (const auto ui : u) {
            double tmp = std::abs(ui);  // df(u) = u
            if (tmp > df_max) df_max = tmp;
        }
        return 0.5 * ex.dx / df_max;
    }
};

struct OpL {
    Vec operator()(const Vec &var, Mesh1d &ex, double t) const {
        const auto &u = var.data;
        size_t n = u.size();
        auto L = std::vector<double>(n);
        for (size_t i = 0; i < n; i++) {
            auto idx = PeriodIndex(n, i);
            double fhat_l = fhat_godunov(u[idx.l()], u[idx.c()]);
            double fhat_r = fhat_godunov(u[idx.c()], u[idx.r()]);
            L[i] = (fhat_l - fhat_r) / ex.dx;
        }
        return Vec{L};
    };

    static double fhat_godunov(double ul, double ur) {
        if (ul <= ur) {  // min
            if (ul * ur > 0) { return std::min(ul * ul / 2, ur * ur / 2); }
            return 0.0;
        }
        return std::max(ul * ul / 2, ur * ur / 2);  // max
    };
};

auto FV_godunov_solverp() {
    using N = OpNull<Vec, Mesh1d>;
    using U = EulerUpdater<Vec, Mesh1d, OpL, GetDt, N, N>;
    return Solver<Vec, Mesh1d, U>{};
}

int main() {
    auto solver = FV_godunov_solverp();
    FV_order_test(order_test_config(), solver, OUTPUT_DIR "/order_p.csv");
    FV_plot_test(plot_config(), solver,
                 {OUTPUT_DIR "/plot_1_p.csv", OUTPUT_DIR "/plot_2_p.csv"});

                 return 0;
}
