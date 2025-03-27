// scroll-effects.js - Scroll-Based Animations
document.addEventListener('DOMContentLoaded', () => {
  const cards = document.querySelectorAll('.feature-card'); // Placeholder for features section
  if (!cards.length) return; // Skip if no feature section yet

  function checkScroll() {
    cards.forEach(card => {
      const rect = card.getBoundingClientRect();
      if (rect.top < window.innerHeight - 100 && !card.classList.contains('animated')) {
        card.style.animation = 'fadeIn 1s ease-in forwards';
        card.classList.add('animated');
      }
    });
  }

  window.addEventListener('scroll', checkScroll);
  checkScroll(); // Initial check
});