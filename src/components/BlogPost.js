import React, { useState, useEffect } from 'react';
import { useParams, Link } from 'react-router-dom'; // Import Link
import './BlogPost.css';
import MarkDown from 'markdown-to-jsx';

const BlogPost = () => {
  const { id } = useParams();
  const [post, setPost] = useState('');

  useEffect(() => {
    // Fetch the content of the markdown file based on the id
    import(`../posts/post${id}.md`)
      .then((res) => {
        fetch(res.default)
          .then((res) => res.text())
          .then((res) => setPost(res));
      })
      .catch((err) => console.log(err));
  }, [id]);

  return (
    <div>
            <Link to="/" className="back-link">Back to Home</Link> {/* Add a link to go back to the home page */}
      <MarkDown>{post}</MarkDown>
      <footer>
        <p>&copy; 2024 Systemfailu.re. All Rights Reserved.</p>
      </footer>
    </div>
    
  );
};

export default BlogPost;
