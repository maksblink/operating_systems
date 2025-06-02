# Wielowątkowa Aplikacja Czatowa w Pythonie

## Przegląd

Ten projekt demonstruje działanie wielowątkowej aplikacji czatowej zbudowanej w Pythonie przy użyciu `socket` do komunikacji sieciowej oraz `threading`, aby obsługiwać wielu klientów jednocześnie. Serwer zarządza połączeniami, przesyłaniem wiadomości i rozłączaniem, podczas gdy klienci mogą wysyłać i odbierać wiadomości w czasie rzeczywistym.

## Funkcje

### Serwer

* Obsługa wielu klientów za pomocą wątków
* Wysyłanie wiadomości do wszystkich podłączonych klientów
* Rejestrowanie pseudonimów użytkowników
* Obsługa rozłączania klientów
* Bezpieczny dostęp do współdzielanych danych dzięki zastosowaniu `threading.Lock`

### Klient

* Łączy się z serwerem czatu przez TCP
* Wysyła i odbiera wiadomości równocześnie dzięki dwóm niezależnym wątkom
* Pozwala opuścić czat komendą `exit`

## Wymagania

* Python w wersji 3.6 lub wyższej

## Kluczowe Koncepcje i Fragmenty Kodu

### Wielowątkowość

Każdy klient obsługiwany jest w osobnym wątku, co zapewnia skalowalność serwera i pozwala na równoległe przetwarzanie wiadomości:

```python
thread = threading.Thread(target=self.handle_client, args=(client,))
thread.start()
```

### Blokowanie dostępu do współdzielonych danych

Aby uniknąć błędów wyścigu (race conditions), każda modyfikacja list `clients` i `nicknames` jest chroniona blokadą:

```python
with self.lock:
    self.clients.append(client)
    self.nicknames.append(nickname)
```

To samo dotyczy ich usuwania.

### Nadawanie wiadomości

Serwer przesyła wiadomość do wszystkich aktywnych klientów. Jeśli wysyłka się nie powiedzie (np. klient się rozłączył), klient jest usuwany z listy:

```python
def broadcast(self, message):
    with self.lock:
        for client in self.clients[:]:
            try:
                client.send(message.encode('utf-8'))
            except:
                self.remove_client(client)
```

### Czyste rozłączanie

Jeśli klient zakończy połączenie lub wystąpi wyjątek, klient zostaje poprawnie usunięty, a pozostałe osoby informowane są o jego odejściu:

```python
def remove_client(self, client):
    with self.lock:
        ...
        self.broadcast(f'{nickname} opuścił czat.')
        client.close()
```

### Komunikacja klient-serwer

Po połączeniu klient otrzymuje zapytanie o pseudonim, który następnie jest rejestrowany przez serwer. Klient może następnie pisać i odbierać wiadomości:

```python
message = self.client.recv(1024).decode('utf-8')
if message == 'NICK':
    self.client.send(self.nickname.encode('utf-8'))
```

## Możliwe Problemy i Błędy

* Utrata połączenia z serwerem może skutkować wyjątkiem po stronie klienta. Obsługiwane jest to w bloku `try-except`, który zamyka klienta.
* W przypadku zamknięcia serwera bez rozłączania klientów, mogą pojawić się błędy transmisji – są one również wychwytywane i obsługiwane.

## Struktura Plików

```
project2/
├── ChatClient.py   # Logika po stronie klienta
├── ChatServer.py   # Logika po stronie serwera
└── README.md       # Dokumentacja projektu
```

## Uruchomienie

### Uruchom serwer

```bash
python ChatServer.py
```

### Uruchom klienta

Otwórz inne okno terminala i wpisz:

```bash
python ChatClient.py
```

Zostaniesz poproszony o podanie pseudonimu i możesz rozpocząć czatowanie.

## Przykład Czatowania

```
$ python ChatClient.py
Wybierz swój pseudonim: Alicja
Połączono z serwerem!
Bob dołączył do czatu!
Bob: Cześć wszystkim!
Alicja: Cześć Bob!
```

## Uwagi

* Upewnij się, że serwer jest uruchomiony przed klientem
* Można uruchomić wielu klientów w osobnych terminalach
* Kod ten nie zawiera zaawansowanych mechanizmów uwierzytelniania czy szyfrowania

## Licencja

Licencja MIT
