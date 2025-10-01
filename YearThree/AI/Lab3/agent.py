import math

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

  def UpdateVector(self, agents, cohesion_weight=0.01, alignment_weight=0.05, separation_weight=0.1, separation_distance=20, max_speed=5):
    neighbors = self.GetNeighbors(agents, 100)

    cohesion = self.GetCohesion(neighbors)
    cohesion = (cohesion[0] * cohesion_weight, cohesion[1] * cohesion_weight)

    alignment = self.GetAlignment(neighbors)
    alignment = (alignment[0] * alignment_weight, alignment[1] * alignment_weight)

    separation = self.GetSeparation(neighbors, separation_distance)
    separation = (separation[0] * separation_weight, separation[1] * separation_weight)

    new_vx = self.Vector[0] + cohesion[0] + alignment[0] + separation[0]
    new_vy = self.Vector[1] + cohesion[1] + alignment[1] + separation[1]

    speed = math.sqrt(new_vx**2 + new_vy**2)
    if speed > max_speed:
      new_vx = (new_vx / speed) * max_speed
      new_vy = (new_vy / speed) * max_speed

    self.Vector = (new_vx, new_vy)

  def GetCohesion(self, neighbors):
    if neighbors:
      sum_x = sum(a.PosX for a in neighbors)
      sum_y = sum(a.PosY for a in neighbors)
      center_x = sum_x / len(neighbors)
      center_y = sum_y / len(neighbors)
      return (center_x - self.PosX, center_y - self.PosY)
    return (0, 0)

  def GetAlignment(self, neighbors):
    if neighbors:
      avg_dx = sum(a.Vector[0] for a in neighbors) / len(neighbors)
      avg_dy = sum(a.Vector[1] for a in neighbors) / len(neighbors)
      return (avg_dx - self.Vector[0], avg_dy - self.Vector[1])
    return (0, 0)

  def GetSeparation(self, neighbors, separation_distance):
    move_x, move_y = 0, 0
    for a in neighbors:
      dist = self.DistanceTo(a)
      if dist < separation_distance and dist > 0: 
        move_x += (self.PosX - a.PosX) / dist
        move_y += (self.PosY - a.PosY) / dist
    return (move_x, move_y)
