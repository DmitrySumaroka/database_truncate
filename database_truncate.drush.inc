<?php
/**
 *@File This command is for truncating any large db
 *
 */

/**
 * Implements hook_drush_command().
 */
function database_truncate_drush_command() {
	$items = array();
  $items['database_truncate'] = array(
    'description' => "Truncate the database",
    'examples' => array(
      'drush dbtrunc' => 'List of all roles',
    ),
    'aliases' => array('bdtrunc'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );
}

/**
 * Deletes the past everything that is no the last 30 days, and deletes useless entries in the db
 */
function drush_database_truncate(){
	//first thing is to see whether the 3 tables that are ussualy huge are there: comment, field_revision_field_issue_changes, field_data_field_issue_changes 
	if (db_table_exists('comment')) {
		$query = db_query("DELETE FROM comment WHERE status = 0");
	}
	if (db_table_exists('field_revision_field_issue_changes')) {
		$query = db_query("DELETE FROM field_revision_field_issue_changes");
	}
	if (db_table_exists('field_data_field_issue_changes')) {
		$query = db_query("DELETE FROM field_data_field_issue_changes");
	}
	//TODO write those queries that were tested so they would remove the proper thing
}