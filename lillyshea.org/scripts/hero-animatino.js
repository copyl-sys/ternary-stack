// hero-animation.js - Hero Section Interactivity
document.addEventListener('DOMContentLoaded', () => {
  const demo = document.getElementById('tritDemo');
  const ctaButtons = document.querySelectorAll('.cta-btn');

  // Initial trit demo
  let baseTrits = [1, 2, 0];
  demo.textContent = `Ternary Live: ${TritJS.toString(baseTrits)} + 011 = ${TritJS.toString(TritJS.add(baseTrits, [0, 1, 1]))}`;

  // Cycle trit demo every 3 seconds
  setInterval(() => {
    const randomTrits = Array(3).fill().map(() => Math.floor(Math.random() * 3));
    const result = TritJS.add(baseTrits, randomTrits);
    demo.textContent = `Ternary Live: ${TritJS.toString(baseTrits)} + ${TritJS.toString(randomTrits)} = ${TritJS.toString(result)}`;
    demo.style.opacity = 0;
    setTimeout(() => {
      demo.style.transition = 'opacity 0.5s';
      demo.style.opacity = 1;
    }, 100);
  }, 3000);

  // CTA hover animation
  ctaButtons.forEach(btn => {
    btn.addEventListener('mouseover', () => {
      btn.style.transform = 'scale(1.05)';
      btn.style.boxShadow = '0 10px 20px rgba(0, 0, 0, 0.3)';
    });
    btn.addEventListener('mouseout', () => {
      btn.style.transform = 'scale(1)';
      btn.style.boxShadow = 'none';
    });
  });
});