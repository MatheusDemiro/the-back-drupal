<?php

require_once BASE_DIR . '\api\connection_api.php';

function register_user_form($form, &$form_state) {  
    $form['user_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Digite seu nome',
      '#size' => 50,
      '#maxlength' => 40,
      '#required' => TRUE,
    );
  
    $form['user_email'] = array(
      '#type' => 'textfield',
      '#title' => 'Digite seu e-mail',
      '#size' => 50,
      '#maxlength' => 50,
      '#required' => TRUE,
    );

    $form['user_type'] = array(
      '#type' => 'select',
      '#title' => 'Digite o tipo da conta',
      '#options' => array(t('Discente'), t('Docente')),
      '#required' => TRUE,
    );
  
    $form['user_password'] = array(
      '#type' => 'password',
      '#title' => 'Digite sua senha',
      '#size' => 50,
      '#maxlength' => 64,
      '#required' => TRUE,
    );
  
    $form['user_submit_button'] = array(
      '#type' => 'submit',
      '#value' => t('Enviar'),
      '#attributes' => array("onclick" => "javascript: this.value='Enviando...'; this.disabled = true; this.form.submit();"),
    );
    
    return $form;
  }

function user_search_form($form, &$form_state) {
  $form['search_username'] = array(
    '#type' => 'textfield',
    '#title' => 'Digite sua busca',
    '#size' => 50,
    '#maxlength' => 50,
    '#required' => FALSE,
  );

  $form['table'] = createTableSelect(json_decode(get_all_users()->data, True));

  $form['user_search_button'] = array(
    '#type' => 'submit',
    '#value' => t('Enviar'),
    '#attributes' => array("onclick" => "javascript: this.value='Enviando...'; this.disabled = true; this.form.submit();"),
  );

  return $form;
}

function table_user_form($form, &$form_state) {
  $sample_data = json_decode(get_all_users()->data, TRUE);

  $form['table'] = createTableSelect($sample_data);

  $form['delete_user_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Excluir usuário'),
    '#name' => 'delete_user',
    '#attributes' => array("onclick" => "javascript: this.value='Enviando...'; this.disabled = true; this.form.submit();"),
  );

  return $form;
}

function createTableSelect($sample_data) {
  $sample_header = array(
    'name' => t('Name'),
    'email' => t('E-mail'),
    'type' => t('Type'),
  );

  $options = array();
  if ($sample_data['sucess']){
    foreach ($sample_data['data'] as $data) {
      $options[$data['id']] = array(
          'name' => $data['name'],
          'email' => $data['email'],
          'type' => $data['type'],
      );
    }
  }

  $form_table = array(
    '#type' => 'tableselect',
    '#header' => $sample_header,
    '#options' => $options,
    '#empty' => t($sample_data['sucess'] ? true: "Nenhuma conexão foi estabelecida. Tente novamente mais tarde ou contate o administrador."),
  );

  return $form_table;
}
