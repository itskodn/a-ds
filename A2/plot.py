import matplotlib.pyplot as plt
import numpy as np

fig, axes = plt.subplots(2, 3, figsize=(18, 10))
fig.suptitle('Сравнительный анализ алгоритмов сортировки', fontsize=16, fontweight='bold')

sizes = []; times = []
with open('mergesort_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1]))
axes[0,0].plot(sizes, times, 'b-', linewidth=2)
axes[0,0].set_title('Standard Merge Sort\n(случайные массивы)')
axes[0,0].set_xlabel('Размер массива')
axes[0,0].set_ylabel('Время (мкс)')
axes[0,0].grid(True, alpha=0.3)

sizes = []; times = []
with open('mergesort_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1]))
axes[0,1].plot(sizes, times, 'r-', linewidth=2)
axes[0,1].set_title('Standard Merge Sort\n(обратные массивы)')
axes[0,1].set_xlabel('Размер массива')
axes[0,1].set_ylabel('Время (мкс)')
axes[0,1].grid(True, alpha=0.3)

sizes = []; times = []
with open('mergesort_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1]))
axes[0,2].plot(sizes, times, 'g-', linewidth=2)
axes[0,2].set_title('Standard Merge Sort\n(почти отсортированные)')
axes[0,2].set_xlabel('Размер массива')
axes[0,2].set_ylabel('Время (мкс)')
axes[0,2].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2]))
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,0].plot(sizes, t5, label='base=5'); axes[1,0].plot(sizes, t10, label='base=10')
axes[1,0].plot(sizes, t15, label='base=15'); axes[1,0].plot(sizes, t20, label='base=20')
axes[1,0].plot(sizes, t30, label='base=30'); axes[1,0].plot(sizes, t50, label='base=50')
axes[1,0].set_title('Гибридная сортировка\n(случайные массивы)')
axes[1,0].set_xlabel('Размер массива')
axes[1,0].set_ylabel('Время (мкс)')
axes[1,0].legend(); axes[1,0].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2]))
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,1].plot(sizes, t5, label='base=5'); axes[1,1].plot(sizes, t10, label='base=10')
axes[1,1].plot(sizes, t15, label='base=15'); axes[1,1].plot(sizes, t20, label='base=20')
axes[1,1].plot(sizes, t30, label='base=30'); axes[1,1].plot(sizes, t50, label='base=50')
axes[1,1].set_title('Гибридная сортировка\n(обратные массивы)')
axes[1,1].set_xlabel('Размер массива')
axes[1,1].set_ylabel('Время (мкс)')
axes[1,1].legend(); axes[1,1].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2]))
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,2].plot(sizes, t5, label='base=5'); axes[1,2].plot(sizes, t10, label='base=10')
axes[1,2].plot(sizes, t15, label='base=15'); axes[1,2].plot(sizes, t20, label='base=20')
axes[1,2].plot(sizes, t30, label='base=30'); axes[1,2].plot(sizes, t50, label='base=50')
axes[1,2].set_title('Гибридная сортировка\n(почти отсортированные)')
axes[1,2].set_xlabel('Размер массива')
axes[1,2].set_ylabel('Время (мкс)')
axes[1,2].legend(); axes[1,2].grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('comparison_analysis.png', dpi=300, bbox_inches='tight')
plt.show()

fig2, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
fig2.suptitle('Сравнительный анализ всех типов данных', fontsize=16, fontweight='bold')

sizes = []; random_times = []; reversed_times = []; almost_times = []
with open('mergesort_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); random_times.append(float(data[1]))
with open('mergesort_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        reversed_times.append(float(data[1]))
with open('mergesort_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        almost_times.append(float(data[1]))

ax1.plot(sizes, random_times, 'b-', label='Случайные', linewidth=2)
ax1.plot(sizes, reversed_times, 'r-', label='Обратные', linewidth=2)
ax1.plot(sizes, almost_times, 'g-', label='Почти отсортированные', linewidth=2)
ax1.set_title('Standard Merge Sort - все типы данных')
ax1.set_xlabel('Размер массива')
ax1.set_ylabel('Время (мкс)')
ax1.legend()
ax1.grid(True, alpha=0.3)

sizes = []; hybrid_random = []; hybrid_reversed = []; hybrid_almost = []
with open('merge&insertion_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        hybrid_random.append(float(data[3]))  
with open('merge&insertion_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        hybrid_reversed.append(float(data[3]))
with open('merge&insertion_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        hybrid_almost.append(float(data[3]))

ax2.plot(sizes, hybrid_random, 'b-', label='Случайные', linewidth=2)
ax2.plot(sizes, hybrid_reversed, 'r-', label='Обратные', linewidth=2)
ax2.plot(sizes, hybrid_almost, 'g-', label='Почти отсортированные', linewidth=2)
ax2.set_title('Hybrid Merge Sort (base=15) - все типы данных')
ax2.set_xlabel('Размер массива')
ax2.set_ylabel('Время (мкс)')
ax2.legend()
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('comparison_all_types.png', dpi=300, bbox_inches='tight')
plt.show()

fig3, ax = plt.subplots(figsize=(12, 8))

sizes = []; standard_times = []; hybrid_best_times = []
with open('mergesort_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); standard_times.append(float(data[1]))
with open('merge&insertion_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        hybrid_best_times.append(float(data[3])) 

ax.plot(sizes, standard_times, 'r-', label='Standard Merge Sort', linewidth=2)
ax.plot(sizes, hybrid_best_times, 'b-', label='Hybrid Merge Sort (base=15)', linewidth=2)
ax.set_title('Сравнение: Standard vs Hybrid Merge Sort\n(случайные массивы)')
ax.set_xlabel('Размер массива')
ax.set_ylabel('Время (мкс)')
ax.legend()
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('comparison_standard_vs_hybrid.png', dpi=300, bbox_inches='tight')
plt.show()
