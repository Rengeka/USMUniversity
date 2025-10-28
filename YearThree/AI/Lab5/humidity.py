class Humidity:
    @staticmethod
    def Min(x):
        return max(0, min(1, (50 - x)/50))
    
    @staticmethod
    def Medium(x):
        if x < 30 or x > 70:
            return 0
        elif x <= 50:
            return (x - 30)/20
        else:
            return (70 - x)/20
    
    @staticmethod
    def Max(x):
        return max(0, min(1, (x - 50)/50))