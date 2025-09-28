class manager:

    def __init__(self, project_name, budget):
        self.project_name = project_name

        self.budget = property()
        self.budget = budget

    def get_project_name(self):
        return self.project_name

    def set_project_name(self, project_name):
        self.project_name = project_name