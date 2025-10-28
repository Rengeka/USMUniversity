class Temperature:
    @staticmethod
    def Min(x):
        return max(0, (15 - x)/15)
    
    @staticmethod
    def Medium(x):
        if x < 10 or x > 30:
            return 0
        elif x <= 20:
            return (x - 10)/10
        else:
            return (30 - x)/10

    @staticmethod
    def Max(x):
        return max(0, min(1, (x - 20)/15))