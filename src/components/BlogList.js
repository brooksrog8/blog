import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import './BlogList.css';

function BlogList() {
  const [posts, setPosts] = useState([]);
  const [categories, setCategories] = useState([]);
  const [selectedCategory, setSelectedCategory] = useState('');

  useEffect(() => {

    const fetchedPosts = ([
      { id: 3, title: "Reverse Engineering Analysis of Opera's Data Collection Part 1: Browser_assistant", fileName: "post3.md", category: "Reverse Engineering"},
      { id: 2, title: "Overview of PE File Structure for Reverse Engineering", fileName: "post2.md", category: "Reverse Engineering Education"},
      { id: 1, title: "AC2 Game Reversing", fileName: "post1.md", category: "Reverse Engineering" }
    ]);
    setPosts(fetchedPosts);
    // Extract categories from posts
    const uniqueCategories = Array.from(new Set(fetchedPosts.map(post => post.category)));
    const categoryObjects = uniqueCategories.map(category => ({ name: category, count: fetchedPosts.filter(post => post.category === category).length }));
    setCategories(categoryObjects);
  }, []);

  const filteredPosts = selectedCategory
    ? posts.filter(post => post.category === selectedCategory)
    : posts;

  const handleCategoryClick = (category) => {
    setSelectedCategory(category);
  };
  return (
    <div className="blog-list-container">
      <h2 className="blog-list-title">
        <a href="/" className="home-link">Sysflow.live</a>
      </h2>
      <h3 className="blog-list-subtitle">A Blog About Reverse Engineering, Malware analysis, and more</h3>
      <hr className="subtitle-line" />
      <div className="content-container">
        <div className="blog-list-content">
        {filteredPosts.map((post) => (
  <div key={post.id} className="blog-list-item">
    <h3 className={`blog-post-title ${post.title === "Title of Blog Post 2" ? "blue-title" : ""}`}>
    <Link to={`/post/${post.id}`} className="blue-post-link">{post.title}</Link>

    </h3>

    <hr className="blog-post-divider" />
  </div>
))}

        </div>
        <div className="categories-section">
          <h3 className="categories-title">Categories</h3>
          <ul className="categories-list">
            {categories.map((category, index) => (
              <li key={index} className="category-item">
                <button
                  onClick={() => handleCategoryClick(category.name)}
                  className={`category-link ${selectedCategory === category.name ? 'active' : ''}`}
                >
                  {category.name} ({category.count})
                </button>
              </li>
            ))}
          </ul>
        </div>
      </div>
      <footer>
        <p>&copy; 2024 Sysflow.live. All Rights Reserved.</p>
      </footer>
    </div>
  );
}

export default BlogList;