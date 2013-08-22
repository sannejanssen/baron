<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 *
 * @link http://api.drupal.org/api/drupal/modules--system--page.tpl.php/7
 *
 * Wunderkraut changes
 * --------------------------------------------------------------------
 * - Add HTML5 asesomenesssss
 * - Alter regions
 * - Remove id's
 * -
 */
?>
<div class="page">
  <header role="banner" class="header">
    <div class="container">

      <div class="top">       
        <?php if ($page['header']): ?>
          <?php print render($page['header']); ?>
        <?php endif; ?>
        
        <?php if ($page['primary_navigation']): ?>
          <nav class="primary-navigation">
            <a href="#" id="mobile-nav-control"><?php print t('Menu'); ?></a>
            <?php print render($page['primary_navigation']); ?>
          </nav>
        <?php endif; ?>
      </div>
      
      <?php if ($logo): ?>
        <figure class="logo">
          <?php if(!$is_front): ?>
            
            <a class="logo-wrapper" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php else: ?>
            <span class="logo-wrapper">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </span>
          <?php endif; ?>

        </figure>
      <?php endif; ?>

    </div>
  </header>

  <div class="container">
    <div role="main" class="main">

      <?php if($page['highlighted']){ ?>
        <?php print render($page['highlighted']); ?>
      <?php } ?>

      <?php if($messages){ ?>
        <div class="drupal-messages">
          <?php print $messages; ?>
        </div>
      <?php } ?>

      <?php if ($title && !$is_front): ?>
        <?php print render($title_prefix); ?>
          <h1><?php print $title; ?></h1>
        <?php print render($title_suffix); ?>
      <?php endif; ?>

      <?php print $breadcrumb; ?>

      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php if ($tabs['#primary']): ?>
        <nav class="tabs"><?php print render($tabs); ?></nav>
      <?php endif; ?>

      <?php print render($page['content']); ?>

    </div>
  </div>

  <footer role="contentinfo" class="footer">
    <div class="container">
      <div class="contact-info">
        <h2>Contactinfo</h2>
        <p>
          <strong>Baron</strong>
          <br />Florian Symoens
          <br />+32 494 27 45 31
          <br />info@baron-gent.be
          <br />Overpoortstraat 48, 9000 GENT
        </p>
      </div>
      
      <div class="footer-nav">
        <h2>Navigatie</h2>
        <ul>
          <li><a href="/">Startpagina</a></li>
          <li><a href="events">Evenementen</a></li>
          <li><a href="pictures">Foto's</a></li>
          <li><a href="videos">Video's</a></li>
          <li class="last"><a href="contact">Contact</a></li>
        </ul>
      </div>

      <ul class="social-links">
        <li class="link facebook"><a href="http://facebook.com">Facebook</a></li>
        <li class="link twitter"><a href="http://facebook.com">Twitter</a></li>
        <li class="link foursquare"><a href="http://facebook.com">Foursquare</a></li>
        <li class="link email"><a href="http://facebook.com">E-mail</a></li>
      </ul>
      <div class="copyright">
        <span class="name">&copy;Baron <?php print date("Y"); ?></span>
        <span class="pipe">|</span>
        <span class="email"><a href="info@baron-gent.be">info@baron-gent.be</a></span>
        <span class="pipe">|</span>
        <span class="humus">this is <a href="http://creating-humus.be">humus</a></span>
      </div>
    </div>
  </footer>

</div>

<?php /*
<div class="page">
  

  <div class="container">
    <?php if ($page['sidebar_first']): ?>
      <aside role="complementary" class="sidebar sidebar_first">
        <?php print render($page['sidebar_first']); ?>
      </aside>
    <?php endif; ?>

    <div role="main" class="main">

      
    </div><!--/main-->

    <?php if ($page['sidebar_second']): ?>
    <aside role="complementary" class="sidebar sidebar_second">
      <?php print render($page['sidebar_second']); ?>
    </aside>
    <?php endif; ?>
  </div>
  
</div>

*/
