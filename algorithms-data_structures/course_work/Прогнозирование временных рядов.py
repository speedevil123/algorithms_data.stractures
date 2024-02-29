import numpy as np
from silence_tensorflow import silence_tensorflow
silence_tensorflow()
import tensorflow as tf
import pandas as pd
import time


while True:
    print("1 - MLP - big data")
    print("2 - MLP - small data\n")
    print("3 - LSTM - big data")
    print("4 - LSTM - small data\n")
    print("5 - CNN - big data")
    print("6 - CNN small data\n")
    print("7 - Выход из программы")
    cmd = input("Выберите пункт меню: ")

    if(cmd == "1"):

        # Считываем и заполняем массивы с 1 и 2 столбца csv файла
        data = pd.read_csv('bitcoin.csv', delimiter=';')
        dates = data['Data'].values
        prices = data['Valueee'].values

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Создаем модель MLP
        model = tf.keras.Sequential([
            tf.keras.layers.Dense(32, activation='relu', input_shape=(1,)),
            tf.keras.layers.Dense(64, activation='relu'),
            tf.keras.layers.Dense(1)
        ])

        # Компилируем модель MLP
        model.compile(optimizer='adam', loss='mse')

        start_time = time.time()
        # Обучаем модель MLP
        model.fit(dates_normalized, prices_normalized, epochs=1000)

        # Предсказываем будущие значения
        future_dates_normalized = np.array([len(prices)+2, len(prices)+3, len(prices)+4, len(prices)+5, len(prices)+6, len(prices)+7, len(prices)+8]) / np.max(dates)
        future_predictions_normalized = model.predict(future_dates_normalized)
        future_predictions = future_predictions_normalized * np.max(prices)

        # Записываем отработанное время
        time_count = time.time() - start_time

        print("Предсказание модели MLP:")
        for date, price in zip(range(len(prices)+2, len(prices)+9), future_predictions):
            print(f"Дата {date}: Предсказанное значение - {float(price):.2f}")

        # Проверка
        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]

        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(len(prices)+2, len(prices)+9), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")

    elif(cmd == "2"):

        
        dates = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21])
        prices = np.array([229.29, 225.85, 225.81, 236.15, 232.08, 234.93, 240.36, 239.02, 236.12, 229.78, 237.33, 243.86, 241.83, 240.3, 242.16, 241.11, 236.38, 236.93, 237.6,236.15,236.8])

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Создаем модель MLP
        model = tf.keras.Sequential([
            tf.keras.layers.Dense(32, activation='relu', input_shape=(1,)),
            tf.keras.layers.Dense(64, activation='relu'),
            tf.keras.layers.Dense(1)
        ])

        # Компилируем модель MLP
        model.compile(optimizer='adam', loss='mse')

        start_time = time.time()

        # Обучаем модель MLP
        model.fit(dates_normalized, prices_normalized, epochs=1000)

        # Предсказываем будущие значения
        future_dates_normalized = np.array([22, 23, 24, 25, 26, 27, 28]) / np.max(dates)
        future_predictions_normalized = model.predict(future_dates_normalized)
        future_predictions = future_predictions_normalized * np.max(prices)

        time_count = time.time() - start_time

        print("Предсказание модели MLP:")
        for date, price in zip(range(22, 29), future_predictions):
            print(f"Дата {date}: Предсказанное значение - {float(price):.2f}")

        # Проверка
        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]

        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(22,29), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")
    if(cmd == "3"):

        # Считываем и заполняем массивы с 1 и 2 столбца csv файла
        data = pd.read_csv('bitcoin.csv', delimiter=';')
        dates = data['Data'].values
        prices = data['Valueee'].values

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Изменяем размерность данных под LSTM
        X = np.reshape(dates_normalized, (len(dates_normalized), 1, 1))  # (samples, timesteps, features)

        # Создаем модель LSTM
        model_lstm = tf.keras.Sequential([
            tf.keras.layers.LSTM(32, activation='relu', input_shape=(1, 1)),
            tf.keras.layers.Dense(1)
        ])

        # Компилируем модель LSTM
        model_lstm.compile(optimizer='adam', loss='mse')

        start_time = time.time()

        # Обучаем модель LSTM
        model_lstm.fit(X, prices_normalized, epochs=1000)

        # Предсказываем будущие значения
        future_dates_normalized = np.array([len(prices)+2, len(prices)+3, len(prices)+4, len(prices)+5, len(prices)+6, len(prices)+7, len(prices)+8]) / np.max(dates)
        future_dates_reshaped = np.reshape(future_dates_normalized, (len(future_dates_normalized), 1, 1))
        future_predictions_normalized = model_lstm.predict(future_dates_reshaped)
        future_predictions = future_predictions_normalized * np.max(prices)

        # Записываем отработанное время
        time_count = time.time() - start_time

        # Выводим предсказания LSTM
        print("Предсказания модели LSTM:")
        for date, price in zip(range(len(prices)+2, len(prices)+9), future_predictions):
            print(f"Дата {date}: Предсказанное значение - {float(price):.2f}")

        # Проверка

        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]


        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(len(prices)+2, len(prices)+9), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")

    elif(cmd == "4"):
        dates = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21])
        prices = np.array([229.29, 225.85, 225.81, 236.15, 232.08, 234.93, 240.36, 239.02, 236.12, 229.78, 237.33, 243.86, 241.83, 240.3, 242.16, 241.11, 236.38, 236.93, 237.6,236.15,236.8])

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Изменяем размерность данных под LSTM
        X = np.reshape(dates_normalized, (len(dates_normalized), 1, 1))  # (samples, timesteps, features)

        # Создаем модель LSTM
        model_lstm = tf.keras.Sequential([
            tf.keras.layers.LSTM(32, activation='relu', input_shape=(1, 1)),
            tf.keras.layers.Dense(1)
        ])

        # Компилируем модель LSTM
        model_lstm.compile(optimizer='adam', loss='mse')

        # Записываем отработанное время
        start_time = time.time()

        # Обучаем модель LSTM
        model_lstm.fit(X, prices_normalized, epochs=1000)

        # Предсказываем будущие значения
        future_dates_normalized = np.array([22, 23, 24, 25, 26, 27, 28]) / np.max(dates)
        future_dates_reshaped = np.reshape(future_dates_normalized, (len(future_dates_normalized), 1, 1))
        future_predictions_normalized = model_lstm.predict(future_dates_reshaped)
        future_predictions = future_predictions_normalized * np.max(prices)

        time_count = time.time() - start_time

        print("Предсказание модели LSTM:")
        for date, price in zip(range(22, 29), future_predictions.flatten()):
            print(f"Date {date}: Предсказанное значение - {price:.2f}")

        # Проверка

        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]

        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(22,29), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")

    elif(cmd == "5"):

        # Считываем и заполняем массивы с 1 и 2 столбца csv файла
        data = pd.read_csv('bitcoin.csv', delimiter=';')
        dates = data['Data'].values
        prices = data['Valueee'].values

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Формируем данные, чтобы они были входными для CNN
        X = dates_normalized.reshape((-1, 1, 1, 1))
        y = prices_normalized.reshape((-1, 1))

        # Создаем модель CNN
        model = tf.keras.Sequential([
            tf.keras.layers.Conv1D(32, kernel_size=1, activation='relu', input_shape=(1, 1)),
            tf.keras.layers.Flatten(),
            tf.keras.layers.Dense(1)
        ])

        # Комплириуем модель CNN
        model.compile(optimizer='adam', loss='mse')

        start_time = time.time()
        # Обучаем модель CNN
        model.fit(X, y, epochs=1000)

        future_dates_normalized = np.array([len(prices)+2, len(prices)+3, len(prices)+4, len(prices)+5, len(prices)+6, len(prices)+7, len(prices)+8]) / np.max(dates)
        future_X = future_dates_normalized.reshape((-1, 1, 1, 1))
        future_predictions_normalized = model.predict(future_X)
        future_predictions = future_predictions_normalized * np.max(prices)

        # Записываем отработанное время
        time_count = time.time() - start_time

        print("Предсказание модели CNN:")
        for date, price in zip(range(len(prices)+2, len(prices)+9), future_predictions.flatten()):
            print(f"Date {date}: Предсказанное значение - {price:.2f}")

        # Проверка

        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]

        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(len(prices)+2, len(prices)+9), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")

    elif(cmd == "6"):
        dates = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21])
        prices = np.array([229.29, 225.85, 225.81, 236.15, 232.08, 234.93, 240.36, 239.02, 236.12, 229.78, 237.33, 243.86, 241.83, 240.3, 242.16, 241.11, 236.38, 236.93, 237.6,236.15,236.8])

        # Нормализуем данные
        dates_normalized = dates / np.max(dates)
        prices_normalized = prices / np.max(prices)

        # Формируем данные, чтобы они были входными для CNN
        X = dates_normalized.reshape((-1, 1, 1, 1))
        y = prices_normalized.reshape((-1, 1))

        # Создаем модель CNN
        model = tf.keras.Sequential([
            tf.keras.layers.Conv1D(32, kernel_size=1, activation='relu', input_shape=(1, 1)),
            tf.keras.layers.Flatten(),
            tf.keras.layers.Dense(1)
        ])

        # Компилируем модель CNN
        model.compile(optimizer='adam', loss='mse')

        start_time = time.time()

        # Обучаем модель CNN
        model.fit(X, y, epochs=1000)

        future_dates_normalized = np.array([22, 23, 24, 25, 26, 27, 28]) / np.max(dates)
        future_X = future_dates_normalized.reshape((-1, 1, 1, 1))
        future_predictions_normalized = model.predict(future_X)
        future_predictions = future_predictions_normalized * np.max(prices)

        # Записываем отработанное время
        time_count = time.time() - start_time


        print("Предсказание модели CNN:")
        for date, price in zip(range(22, 29), future_predictions.flatten()):
            print(f"Date {date}: Предсказанное значение - {price:.2f}")

        # Проверка

        real_7d_prices = [231.95, 234.02, 235.34, 240.35, 238.87, 240.95, 237.11]

        # Считаем отклонение в процентах
        deviations = [(pred - real) / real * 100 for pred, real in zip(future_predictions.flatten(), real_7d_prices)]

        print("Отклонения от реальных цен:")
        for date, deviation in zip(range(22,29), deviations):
            print(f"Date {date}: Отклонение - {deviation:.2f}%")

        average_dev = sum(deviations)/len(deviations)

        print(f"Время прогнозирования: {round(time_count*100, 2)}ms")
        print(f"Среднее отклонение: {round(average_dev, 2)}%")
    elif(cmd == "7"):
        exit()
    else:
        print("Такого пункта меню не существует")
