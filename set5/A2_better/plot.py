import os
os.environ.setdefault('MPLCONFIGDIR', '/tmp/mplconfig')
os.environ.setdefault('XDG_CACHE_HOME', '/tmp/fontcache')
os.makedirs(os.environ['MPLCONFIGDIR'], exist_ok=True)
os.makedirs(os.environ['XDG_CACHE_HOME'], exist_ok=True)
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd

DIR = os.path.dirname(os.path.abspath(__file__))

def plot_graph1():
    df = pd.read_csv(os.path.join(DIR, 'single_stream.csv'))
    plt.figure(figsize=(10, 6))
    plt.plot(df['processed'], df['exact_f0'], 'b-o', ms=4, label='$F_0^t$ (точное)')
    plt.plot(df['processed'], df['hll_std'], 'r--s', ms=4, label='$N_t$ (стандартный)')
    plt.plot(df['processed'], df['hll_packed'], 'g--^', ms=4, label='$N_t$ (улучшенный)')
    plt.xlabel('Размер обработанной части потока')
    plt.ylabel('Количество уникальных элементов')
    plt.title('График №1: Сравнение стандартного и улучшенного HLL')
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(os.path.join(DIR, 'graph1_comparison.png'), dpi=150)
    plt.close()
    print('  graph1_comparison.png')

def plot_graph2():
    df = pd.read_csv(os.path.join(DIR, 'statistics.csv'))
    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    ax = axes[0]
    ax.plot(df['processed'], df['mean_f0'], 'b-o', ms=3, label='$\\overline{F_0^t}$')
    ax.plot(df['processed'], df['mean_std'], 'r-s', ms=3, label='$\\mathbb{E}(N_t)$ std')
    ax.fill_between(df['processed'],df['mean_std'] - df['std_std'],df['mean_std'] + df['std_std'],
    alpha=0.25, color='red', label='$\\pm \\sigma$')
    ax.set_xlabel('Размер обработанной части потока')
    ax.set_ylabel('Количество уникальных элементов')
    ax.set_title('Стандартный алгоритм')
    ax.legend(fontsize=9)
    ax.grid(alpha=0.3)
    ax = axes[1]
    ax.plot(df['processed'], df['mean_f0'], 'b-o', ms=3, label='$\\overline{F_0^t}$')
    ax.plot(df['processed'], df['mean_packed'], 'g-^', ms=3, label='$\\mathbb{E}(N_t)$ улучш.')
    ax.fill_between(df['processed'],df['mean_packed'] - df['std_packed'],df['mean_packed'] + df['std_packed'],
    alpha=0.25, color='green', label='$\\pm \\sigma$')
    ax.set_xlabel('Размер обработанной части потока')
    ax.set_ylabel('Количество уникальных элементов')
    ax.set_title('Улучшенный алгоритм −25% памяти)')
    ax.legend(fontsize=9)
    ax.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(os.path.join(DIR, 'graph2_statistics.png'), dpi=150)
    plt.close()
    print('  graph2_statistics.png')

def plot_graph3():
    df = pd.read_csv(os.path.join(DIR, 'b_comparison.csv'))
    plt.figure(figsize=(10, 6))
    plt.plot(df['B'], df['rel_error'], 'o-', label='Относительная ошибка')
    theo_104 = 1.04 / (df['m'] ** 0.5)
    theo_130 = 1.30 / (df['m'] ** 0.5)
    plt.plot(df['B'], theo_104, 'k--', label='1.04 / sqrt(m)')
    plt.plot(df['B'], theo_130, 'k-.', label='1.30 / sqrt(m)')
    plt.xlabel('B (кол-во бит индекса)')
    plt.ylabel('Относительная ошибка')
    plt.title('График №3: Ошибка HyperLogLog при разных B')
    plt.legend()
    plt.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(os.path.join(DIR, 'graph3_comparison.png'), dpi=150)
    plt.close()
    print('  graph3_comparison.png')

def plot_memory():
    B = 14
    m = 2 ** B
    mem_std = m
    mem_packed = (m // 4) * 3
    fig, ax = plt.subplots(figsize=(7, 5))
    bars = ax.bar(['Стандартный', 'Улучшенный'], [mem_std, mem_packed],color=['#e74c3c', '#2ecc71'], width=0.5)
    for bar, val in zip(bars, [mem_std, mem_packed]): ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 200,
    f'{val} байт', ha='center', fontsize=12, fontweight='bold')
    ax.set_ylabel('Память')
    ax.set_title(f'Потребление памяти HyperLogLog\n' f'Экономия {(1 - mem_packed/mem_std)*100:.0f}%')
    ax.set_ylim(0, mem_std * 1.2)
    ax.grid(axis='y', alpha=0.3)
    plt.tight_layout()
    plt.savefig(os.path.join(DIR, 'graph4_memory.png'), dpi=150)
    plt.close()
    print('  graph4_memory.png')

if __name__ == '__main__':
    plot_graph1()
    plot_graph2()
    plot_graph3()
    plot_memory()
    print('Done.')
