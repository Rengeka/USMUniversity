from agent import Agent
import random
import pygame

def InitWindow(width, height):
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption("Bodis alg")
    clock = pygame.time.Clock()
    return screen, clock

def DrawAgent(screen, agent):
    pygame.draw.circle(screen, (255, 0, 0), (int(agent.PosX), int(agent.PosY)), 5)

def Run(clock, screen, agents, width, height):
    running = True
    while running:
        clock.tick(30)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        for agent in agents:

            agent.UpdateVector(agents, 0.01, 0.1, 0.2)

            agent.PosX += agent.Vector[0]
            agent.PosY += agent.Vector[1]

            if agent.PosX < 0 or agent.PosX > width:
                agent.Vector = (-agent.Vector[0], agent.Vector[1])
            if agent.PosY < 0 or agent.PosY > height:
                agent.Vector = (agent.Vector[0], -agent.Vector[1])

        screen.fill((255, 255, 255))
        for agent in agents:
            DrawAgent(screen, agent)

        pygame.display.flip()

agents = []
for i in range(10):
    x = random.randint(0, 800)
    y = random.randint(0, 600)
    dx = random.choice([-2, -1, 0, 1, 2])
    dy = random.choice([-2, -1, 0, 1, 2])
    agents.append(Agent(x, y, (dx, dy)))

(screen, clock) = InitWindow(800, 600)
Run(clock, screen, agents, 800, 600)

pygame.quit()