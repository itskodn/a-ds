import matplotlib.pyplot as plt
import numpy as np

wide_data = np.loadtxt('wide.txt', skiprows=1)
narrow_data = np.loadtxt('narrow.txt', skiprows=1)

exact_area = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1

wide_error_percent = wide_data[:, 2] * 100
narrow_error_percent = narrow_data[:, 2] * 100

plt.figure(figsize=(15, 10))

plt.subplot(2, 1, 1)
plt.plot(wide_data[:, 0], wide_data[:, 1], 'b-', alpha=0.7, label='Широкая область', linewidth=1)
plt.plot(narrow_data[:, 0], narrow_data[:, 1], 'r-', alpha=0.7, label='Узкая область', linewidth=1)
plt.axhline(y=exact_area, color='k', linestyle='--', label=f'Точная площадь ({exact_area:.4f})', linewidth=2)
plt.xlabel('Количество точек N')
plt.ylabel('Площадь')
plt.title('Зависимость приближенной площади от N')
plt.legend()
plt.grid(True, alpha=0.3)
plt.xlim(0, 100000)

plt.subplot(2, 1, 2)
plt.plot(wide_data[:, 0], wide_error_percent, 'b-', alpha=0.7, label='Широкая область', linewidth=1)
plt.plot(narrow_data[:, 0], narrow_error_percent, 'r-', alpha=0.7, label='Узкая область', linewidth=1)
plt.xlabel('Количество точек N')
plt.ylabel('Относительная ошибка (%)')
plt.title('Зависимость относительной ошибки от N')
plt.legend()
plt.grid(True, alpha=0.3)
plt.ylim(0, 10)
plt.xlim(0, 100000)

plt.tight_layout()
plt.savefig('monte_carlo_results.png', dpi=300, bbox_inches='tight')
plt.show()

final_wide = wide_data[-1, 1]
final_narrow = narrow_data[-1, 1]
final_wide_error = wide_error_percent[-1]
final_narrow_error = narrow_error_percent[-1]


