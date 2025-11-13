import random
import math
import matplotlib.pyplot as plt

# --- Целевая функция ---
def f(x):
    return math.sin(4 * math.pi * x) ** 2 + 0.3 * x

# --- Декодирование хромосомы ---
def decode(chromosome):
    # chromosome — список битов длины L
    value = int(''.join(map(str, chromosome)), 2)
    return value / (2**len(chromosome) - 1)  # нормализуем в [0, 1]

# --- Инициализация популяции ---
def initialize_population(N, L):
    return [[random.randint(0, 1) for _ in range(L)] for _ in range(N)]

# --- Оценка приспособленности ---
def evaluate_population(pop):
    return [f(decode(ind)) for ind in pop]

# --- Селекция (рулетка) ---
def selection(pop, fitness):
    total_fit = sum(fitness)
    probs = [fit / total_fit for fit in fitness]
    chosen = random.choices(pop, weights=probs, k=2)
    return chosen[0][:], chosen[1][:]

# --- Кроссовер ---
def crossover(p1, p2, pc):
    if random.random() < pc:
        point = random.randint(1, len(p1) - 2)
        print(f"Кроссовер между {p1} и {p2} в точке {point}")
        c1 = p1[:point] + p2[point:]
        c2 = p2[:point] + p1[point:]
        return c1, c2
    return p1[:], p2[:]

# --- Мутация ---
def mutate(chromosome, pm):
    for i in range(len(chromosome)):
        if random.random() < pm:
            chromosome[i] = 1 - chromosome[i]
            print(f"Мутация: бит {i} изменён")
    return chromosome

# --- Главный цикл ГА ---
def genetic_algorithm(N=4, L=4, pc=0.8, pm=0.05, G=30):
    pop = initialize_population(N, L)
    best_values = []

    for gen in range(G):
        fitness = evaluate_population(pop)
        decoded = [decode(ind) for ind in pop]

        max_fit = max(fitness)
        avg_fit = sum(fitness) / len(fitness)
        min_fit = min(fitness)
        best_values.append(max_fit)

        print(f"\n--- Поколение {gen + 1} ---")
        for i in range(N):
            print(f"{i}: {pop[i]} -> x={decoded[i]:.4f}, f={fitness[i]:.4f}")
        print(f"Макс: {max_fit:.4f}, Мин: {min_fit:.4f}, Средн: {avg_fit:.4f}")

        # Создаём новое поколение
        new_pop = []
        while len(new_pop) < N:
            p1, p2 = selection(pop, fitness)
            c1, c2 = crossover(p1, p2, pc)
            c1 = mutate(c1, pm)
            c2 = mutate(c2, pm)
            new_pop.extend([c1, c2])
        pop = new_pop[:N]

    # --- Итог ---
    fitness = evaluate_population(pop)
    decoded = [decode(ind) for ind in pop]
    best_idx = fitness.index(max(fitness))
    print(f"\nЛучшее решение: x* = {decoded[best_idx]:.4f}, f(x*) = {fitness[best_idx]:.4f}")

    plt.plot(best_values)
    plt.title("Изменение максимального значения fitness по поколениям")
    plt.xlabel("Поколение")
    plt.ylabel("Максимальный fitness")
    plt.grid(True)
    plt.show()

# --- Запуск ---
genetic_algorithm(N=6, L=4, pc=0.8, pm=0.05, G=40)