class Wind:
    @staticmethod
    def Min(x):
        return max(0, min(1, (20 - x)/20))
    
    @staticmethod
    def Medium(x):
        if x < 10 or x > 40:
            return 0
        elif x <= 25:
            return (x - 10)/15
        else:
            return (40 - x)/15
    
    @staticmethod
    def Max(x):
        return max(0, min(1, (x - 25)/25))