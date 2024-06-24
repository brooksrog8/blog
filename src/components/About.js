import React from 'react';

const styles = {
  container: {
    maxWidth: '600px',
    margin: '0 auto',
    padding: '20px',
    backgroundColor: '#333',
    boxShadow: '0 0 10px rgba(0, 0, 0, 0.1)',
    borderRadius: '5px',
    fontFamily: 'Arial',
    lineHeight: '1.6',
  },
  heading: {
    textAlign: 'center',
    fontSize: '2.5em',
    color: '#fff',
    marginBottom: '20px',
  },
  paragraph: {
    fontSize: '1.2em',
    color: '#fff',
    textAlign: 'left',
    marginBottom: '15px',
  },
  contactInfo: {
    marginTop: '20px',
    fontSize: '1.1em',
    color: '#007bff',
  },
};

function About() {
    return (
      <div style={styles.container}>
        <h1 style={styles.heading}>About</h1>
        <p style={styles.paragraph}>
          My name is Brooks. If you're reading this, you most likely already know that I reverse engineer malware or game-related software.
          I enjoy breaking down systems at their lowest level and have dedicated myself to the computer security realm for about 5 years now. I am open to help or be paid to reverse software
          or embedded systems if anyone has an interesting project.
        </p>
        <p style={styles.contactInfo}>
          Phone: (918) 399-8741 <br />
          Discord: brooksrogers8
        </p>
      </div>
    );
  }
  
  export default About;