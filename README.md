### Description

This code implements a **Three-Level Password System** designed to enhance security through multiple layers of authentication. It combines traditional password mechanisms with additional features to protect user accounts from unauthorized access. Here’s how the system works and what the code is designed to achieve:

#### Key Features:

1. **Textual Password**: 
   - Users create a standard textual password.
   - The password is hashed using a custom hashing function combined with a salt value.
   - To further secure the password, it undergoes stretching (repeated hashing) to resist brute-force attacks.

2. **Graphical Password**: 
   - Users set a graphical password consisting of a pattern of 5 integers.
   - During login, users must correctly enter this pattern to gain access.

3. **Two-Factor Authentication (2FA)**:
   - Users provide a two-factor authentication code.
   - This code is validated against the stored code for additional security.

4. **Account Lockout**:
   - The system tracks failed login attempts.
   - After a maximum number of failed attempts (3), the account is locked to prevent further login attempts.

#### Detailed Functionality:

1. **Sign Up**:
   - Users choose a username, set a textual password, define a graphical password pattern, and provide a 2FA code.
   - The system hashes and salts the textual password, stores the graphical password, and saves the 2FA code.
   - Accounts are initialized with zero failed login attempts and are not locked.

2. **Login**:
   - Users provide their username and must enter their textual password, graphical password pattern, and 2FA code.
   - The system validates each component:
     - Textual password is hashed and checked.
     - Graphical password pattern is compared.
     - 2FA code is verified.
   - If any component is incorrect, the system increments the failed attempts counter.
   - After reaching the maximum allowed attempts, the account is locked.

3. **User Database**:
   - Maintains an in-memory database of users, including their hashed password, graphical password, 2FA code, failed attempts count, and lock status.

4. **User Interface**:
   - Provides a simple console menu for users to sign up, log in, or exit the program.
   - Handles invalid input and ensures users can navigate through the options easily.

### Goals Achieved:

- **Enhanced Security**: 
  - By combining textual passwords with graphical passwords and 2FA, the system significantly strengthens authentication.
  - Hashing, salting, and stretching the password adds layers of security against common attack vectors.

- **User-Friendly Interface**:
  - The system features a straightforward console-based interface for interaction.
  - Prompts guide users through the sign-up and login processes clearly.

- **Account Protection**:
  - Locking accounts after multiple failed attempts prevents brute-force attacks and protects against unauthorized access.

Overall, the Three-Level Password System aims to provide robust security while maintaining ease of use and simplicity in the authentication process.
