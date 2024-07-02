class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        self._size = 0

    def __str__(self):
           return "🍪" * self._size


    def deposit(self, n):
        if (self.size + n) > self.capacity:
            raise ValueError
        else:
            self.size += n

    def withdraw(self, n):
        if (self.size - n) < 0:
            raise ValueError
        else:
            self.size -+ n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar()
    print(f"{jar.size}")
    print(f"{jar.capacity}")
    print(str(jar))




main()