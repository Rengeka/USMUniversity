class DryTime:
    @staticmethod
    def Short(x):
        if x <= 10:
            return 1
        elif 10 < x < 20:
            return (20 - x) / 10
        else:
            return 0

    @staticmethod
    def Medium(x):
        if 10 < x < 20:
            return (x - 10) / 10
        elif 20 <= x <= 30:
            return (30 - x) / 10
        else:
            return 0

    @staticmethod
    def Long(x):
        if x >= 30:
            return 1
        elif 20 < x < 30:
            return (x - 20) / 10
        else:
            return 0
