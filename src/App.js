import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import BlogList from './components/BlogList';
import BlogPost from './components/BlogPost';
import About from './components/About';
import Navbar from './components/Navbar';
const App = () => {
  return (
    <Router>
      <div>
        <Navbar />
      <Routes>
        <Route path="/" element={<BlogList />} />
        <Route path="/post/:id" element={<BlogPost />} />
        <Route path="/about" element={<About />} />
      </Routes>
      </div>
    </Router>
  );
};

export default App;
