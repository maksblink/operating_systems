Oto plik README.md w formacie Markdown:


# 🚀 Wielowątkowy Serwer Czatu w Pythonie

![Python](https://img.shields.io/badge/Python-3.6%2B-blue)
![Socket](https://img.shields.io/badge/Socket-Networking-orange)
![Threading](https://img.shields.io/badge/Threading-Multithreaded-brightgreen)

## 📋 Opis projektu

Projekt implementuje wielowątkowy serwer czatu z wykorzystaniem:
- `socket` do komunikacji sieciowej
- `threading` do obsługi wielu klientów jednocześnie

## 🌟 Funkcjonalności

### Serwer
- 🧵 Tworzy osobny wątek dla każdego klienta
- 🔒 Synchronizacja wiadomości między klientami
- 📢 Rozsyłanie wiadomości do wszystkich uczestników
- 🏷️ Zarządzanie nickami użytkowników
- ♻️ Obsługa rozłączeń klientów

### Klient
- ✍️ Wysyłanie wiadomości
- 👀 Wyświetlanie wiadomości od innych
- 🚪 Możliwość opuszczenia czatu (`exit`)

## 🛠️ Wymagania

- Python 3.6+
- Terminal/system operacyjny obsługujący wielowątkowość

## 🚀 Uruchomienie

1. **Serwer**:
```bash
python server.py
```

2. **Klient** (w osobnym terminalu):
```bash
python client.py
```

## 🖥️ Przykładowa sesja

```
$ python client.py
Wybierz swój nickname: Alice
Połączono z serwerem!
Bob dołączył do czatu!
Bob: Cześć wszystkim!
Alice: Witaj Bob!
```

## 📁 Struktura projektu

```
chat-server/
├── server.py        # Implementacja serwera
├── client.py        # Implementacja klienta
└── README.md        # Dokumentacja
```

## 📜 Licencja

MIT License - [LICENSE](LICENSE)

---

<div align="center">
  <p>🎉 <em>Prosty czat wielowątkowy w Pythonie</em> 🎉</p>
</div>
```

Ten plik zawiera:
- Nagłówek z emoji i badge'ami
- Sekcje z opisem projektu i funkcjonalności
- Instrukcję uruchomienia
- Przykładową sesję
- Strukturę projektu
- Informację o licencji

Format jest przyjazny dla GitHub/GitLab i innych platform obsługujących Markdown. Możesz go łatwo zmodyfikować dodając np. sekcję "Autorzy" lub "Wkład w projekt".