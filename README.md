  <h1>minishell</h1>

  <h2>Introduction</h2>
  <p>Welcome to the <strong>minishell</strong> project, part of the curriculum at 42. This project aims to create a simple shell that mimics the behavior of common UNIX command interpreters. This project helps you understand how command-line interfaces work and deepens your knowledge of process creation and management, file descriptors, and signal handling.</p>

  <h2>Objective</h2>
  <p>The objective of the "minishell" project is to build a basic shell that can interpret and execute commands provided by the user. The shell should handle built-in commands as well as external programs, manage environment variables, and provide a simple command-line interface for user interaction.</p>

  <h2>Requirements</h2>
  <p>The minishell program must meet the following requirements:</p>
  <ul>
      <li>Display a prompt and wait for user input.</li>
      <li>Execute commands entered by the user.</li>
      <li>Implement built-in commands such as <code>echo</code>, <code>cd</code>, <code>unset</code>, <code>export</code>, <code>env</code>, and <code>pwd</code>.</li>
      <li>Handle command-line arguments and environment variables.</li>
      <li>Support input and output redirection.</li>
      <li>Handle pipes to connect multiple commands.</li>
      <li>Manage signals, including handling <code>Ctrl+C</code>, <code>Ctrl+D</code>, and <code>Ctrl+\</code>.</li>
      <li>Implement error handling and display appropriate error messages.</li>
  </ul>

  <h2>Key Concepts</h2>
  <ul>
      <li><strong>Command Parsing</strong>: Interpreting and breaking down user input into commands and arguments.</li>
      <li><strong>Process Creation and Management</strong>: Creating and managing processes using system calls like <code>fork</code>, <code>execve</code>, and <code>wait</code>.</li>
      <li><strong>File Descriptors</strong>: Managing input and output streams using file descriptors for redirection and pipes.</li>
      <li><strong>Environment Variables</strong>: Using and modifying environment variables to store configuration settings and pass information to processes.</li>
      <li><strong>Signal Handling</strong>: Responding to and managing signals to control process behavior and handle user interruptions.</li>
  </ul>
  
  <h2>Conclusion</h2>
  <p>The <strong>minishell</strong> project provides a hands-on opportunity to understand how a shell works, focusing on command parsing, process management, and input/output handling. By completing this project, you will gain practical experience in building a functional command-line interface, enhancing your skills in C programming and UNIX system calls.</p>
