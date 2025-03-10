# Role Based Access Control Optimization

A C implementation of a role-based access control (RBAC) mining algorithm that generates optimal role assignments while respecting user and permission cardinality constraints.
This tool processes user-permission relationships from input files and outputs user-role (UA) and permission-role (PA) assignment matrices, minimizing the number of roles while maintaining complete coverage of the original access control requirements.

## Features

- Processes user-permission relationship data from input files
- Supports configurable role usage constraints (maximum roles per user)
- Supports configurable permission distribution constraints (maximum permissions per role)
- Implements both user-centric and permission-centric role formation approaches
- Generates optimal user-role (UA) and permission-role (PA) assignment matrices
- Guarantees complete coverage of the original access control requirements

## Algorithm

RoleMinerC implements a two-phase algorithm:

1. **Phase 1**: Identifies users and permissions with minimal connections, creating roles based on these minimal sets to efficiently cover the access control graph.

2. **Phase 2**: Handles remaining uncovered user-permission relationships, focusing on users and permissions that are close to their cardinality constraints.

The algorithm alternates between user-centric role formation (`form_role`) and permission-centric role formation (`dual_of_form_role`) based on which approach provides better coverage at each step.

## Usage

1. Compile the Main C File with
   
```bash
gcc -o roleminer main.c
```

And then prepare your UPA (User-Permission Assignment) matrix in a text file with the following format:
   - First line: Number of users
   - Second line: Number of permissions
   - Subsequent lines: Space-separated pairs of "user_id permission_id" (1-indexed)

Example UPA file (`example.txt`):
```
3
4
1 1
1 2
2 2
2 3
3 3
3 4
```

2. Run the compiled program:
```bash
./roleminer
```

3. When prompted, enter:
   - The name of the UPA matrix file (e.g., `example.txt`)
   - The maximum number of roles per user (role-usage cardinality constraint)
   - The maximum number of permissions per role (permission-distribution cardinality constraint)

4. The program will generate two output files:
   - `<input_filename>_UA.txt`: The User-Role Assignment matrix
   - `<input_filename>_PA.txt`: The Permission-Role Assignment matrix

## Limitations

- Maximum supported sizes:
  - Up to 5000 users
  - Up to 5000 roles
  - Up to 5000 permissions
  
