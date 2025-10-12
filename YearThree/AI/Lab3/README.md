# Lab 3
Topic: Boids algorithm

Student: Stanisalv Ciobanu

Group: I2302

Teacher: V.Trebes

# Structure

Project contains agent.py with core agent logic

And main.py with execution environment based on pygame library

Agent contains coordinates and movement vector:
```python
class Agent:
  def __init__(self, posX, posY, vector):
    self.PosX = posX
    self.PosY = posY
    self.Vector = vector

  def DistanceTo(self, other):
    dx = self.PosX - other.PosX
    dy = self.PosY - other.PosY
    return math.sqrt(dx**2 + dy**2)

  def GetNeighbors(self, agents, radius):
    return [a for a in agents if a is not self and self.DistanceTo(a) <= radius]
```

It also contains method for udating his own position:
```python
  def UpdateVector(self, agents, cohesion_weight=0.01, alignment_weight=0.05, separation_weight=0.1, separation_distance=20, max_speed=5):
```

main.py contains methods for creating and running environment and drawing agents:
```python
def InitWindow(width, height):
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Bodis alg")
    clock = pygame.time.Clock()
    return screen, clock

def DrawAgent(screen, agent):
    pygame.draw.circle(screen, (255, 0, 0), (int(agent.PosX), int(agent.PosY)), 5)

def Run(clock, screen, agents, width, height):
    ...
```

# How to run

Use ```python main.py``` to run application